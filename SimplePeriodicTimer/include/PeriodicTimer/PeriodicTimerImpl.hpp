#ifndef PERIODICTIMERIMPL_HPP_
#define PERIODICTIMERIMPL_HPP_

#include <PeriodicTimer/DurationStreamOperator.hpp>
#include <PeriodicTimer/PeriodicTimer.hpp>
#include <PeriodicTimer/ReceiversDefaultImpl.hpp>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

namespace SimplePeriodicTimer{

template<class Receiver_, std::size_t numReceivers_, class IntervalDuration_=std::chrono::milliseconds>
struct DefaultTimerRepository{
	using Receiver = Receiver_;
	using IntervalDuration = IntervalDuration_;
	static constexpr std::size_t numReceivers = numReceivers_;

//	using MemberFunction = void(Receiver::*)();
	using Receivers = ReceiversDemoImpl<Receiver, numReceivers>;
};

template<class TimerRepository>
class PeriodicTimerImpl : public PeriodicTimer<typename TimerRepository::Receiver>{
public:
	using this_type = PeriodicTimerImpl<TimerRepository>;
	using base_type = PeriodicTimer<typename TimerRepository::Receiver>;

	using MemberFunction = typename base_type::MemberFunction;

	using IntervalDuration = typename TimerRepository::IntervalDuration;
	using Receiver = typename TimerRepository::Receiver;
	using Receivers = typename TimerRepository::Receivers;

	using Thread = std::thread;
	using Mutex = std::recursive_mutex;
	using Guard = std::unique_lock<Mutex>;

	// Timers must not be copied
	PeriodicTimerImpl(PeriodicTimerImpl const&) = delete;
	PeriodicTimerImpl& operator=(PeriodicTimerImpl const&) = delete;

	PeriodicTimerImpl()
	: PeriodicTimerImpl(nullptr, IntervalDuration(500))
	{}
	PeriodicTimerImpl(IntervalDuration intervalDuration)
	: PeriodicTimerImpl(nullptr, intervalDuration)
	{}
	PeriodicTimerImpl(MemberFunction function, IntervalDuration intervalDuration=IntervalDuration(500))
	:
		intervalDuration(intervalDuration),
		receivers()
	{}

	void addReceiver(Receiver& receiver){
		Guard guard(myMutex);
		//std::cout << "addReceiver()" << std::endl;
		receivers.addReceiver(receiver);
		if(threadToBeActivated()){
			startThread();
		}
	}
	void setCallback(MemberFunction function){
		Guard guard(myMutex);
		//std::cout << "Timer::setCallback()" << std::endl;
		receivers.setCallback(function);
		if(threadToBeActivated()){
			startThread();
		}
	}
	void removeReceiver(Receiver& receiver){
//		std::cout << "Timer::removeReceiver()" << " befor Guard" << std::endl;
		Guard guard(myMutex);
//		std::cout << "Timer::removeReceiver()" << std::endl;
		receivers.removeReceiver(receiver);
	}
	void setIntervalDuration(IntervalDuration intervalDuration){
		Guard guard(myMutex);
		//std::cout << "Timer::setIntervalDuration(): " << intervalDuration << std::endl;
		this->intervalDuration = intervalDuration;
	}
	void setIntervalDuration(unsigned long long intervalDuration){
		setIntervalDuration(IntervalDuration(intervalDuration));
	}
	bool isThreadActive(){
		Guard guard(myMutex);
		return threadActive;
	}
private:
	//================================
	// will be called under guard
	//================================
	bool threadToBeActivated(){
		return receivers.canBeInvoked() && !threadActive;
	}
	void startThread(){
		Thread t(&this_type::run, this);
		threadActive= true;
		t.detach();
	}
	// return of Thread callback run() ends thread
	void run(){
		using namespace std;
		Guard guard(myMutex, std::defer_lock);
		while(true){
			auto beforeInvoke = std::chrono::steady_clock::now();
			guard.lock();
			if(!receivers.hasReceiver()){
				threadActive = false;
//				cout << "run() thread ended: " << this_thread::get_id() << endl;
				guard.unlock();
				return; // ends the thread
			}
			receivers.invoke();
			// may changed from receivers
			std::chrono::nanoseconds intervalDuration(this->intervalDuration);
			guard.unlock();
			auto nextRun = beforeInvoke + intervalDuration;
			std::this_thread::sleep_until(nextRun);

			// would be shifting by the processing time of receivers.invoke()
//			std::this_thread::sleep_for(intervalDuration);
		}
	}
private:
	Mutex myMutex;
	IntervalDuration intervalDuration{500};
	bool threadActive = false;
	Receivers receivers;
};

} //namespace SimplePeriodicTimer

#endif /* PERIODICTIMERIMPL_HPP_ */
