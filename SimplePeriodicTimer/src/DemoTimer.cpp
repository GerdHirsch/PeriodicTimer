#include <PeriodicTimer/PeriodicTimerImpl.hpp>
#include <iostream>
#include <chrono>

using namespace std;

namespace{
class MyClass{
public:
	MyClass(std::string name, SimplePeriodicTimer::PeriodicTimer<MyClass>& timer):name(std::move(name)), timer(&timer){}
	~MyClass(){
		timer->removeReceiver(*this);
	}

	void doSomething(){
		std::cout << name << std::endl;
	}
	std::string name;
	SimplePeriodicTimer::PeriodicTimer<MyClass>* timer;
};

}
namespace PT = SimplePeriodicTimer;

void demoTimer(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	using IntervalDuration = std::chrono::milliseconds;
	IntervalDuration sleepDuration(2500);

	using TimerRepo = PT::DefaultTimerRepository<MyClass, 3>;
	PT::PeriodicTimerImpl<TimerRepo> timerImpl;
	PT::PeriodicTimer<MyClass> & timer = timerImpl;

	timer.setCallback(&MyClass::doSomething);
	timer.setIntervalDuration(500);

	MyClass a1("a1", timer), a2("a2", timer);

	std::cout << "add a1" << std::endl;
	timer.addReceiver(a1);
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);

	std::cout << "addReceiver a2" << std::endl;
	timer.addReceiver(a2);
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);
	//=================================================
	// remove a2
	std::cout << "remove a2" << std::endl;
	timer.removeReceiver(a2);
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);
	// removeReceiver a1
	std::cout << "removeReceiver a1" << std::endl;
	timer.removeReceiver(a1);
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);
	//=================================================
	// addReceiver a3, a2
	{
		MyClass a3("a3", timer);
		std::cout << "addReceiver a3" << std::endl;
		timer.addReceiver(a3);
		timer.setIntervalDuration(250);
		std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);
		std::cout << "addReceiver a2" << std::endl;
		timer.addReceiver(a2);
		std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);
	}
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);
	//=================================================
	// removeReceiver a2
	std::cout << "removeReceiver a2" << std::endl;
	timer.removeReceiver(a2);
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);
	cout << "end demoTimer()" << endl;
}


void demo2Timer(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	using IntervalDuration = std::chrono::milliseconds;
	IntervalDuration sleepDuration(2500);

	using TimerRepo = PT::DefaultTimerRepository<MyClass, 3>;
	PT::PeriodicTimerImpl<TimerRepo> timer1(&MyClass::doSomething);
	PT::PeriodicTimerImpl<TimerRepo> timer2(&MyClass::doSomething);

	MyClass a1("a1", timer1), a2("a2", timer2);

	std::cout << "addReceiver a1" << std::endl;
	timer1.addReceiver(a1);
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);

	std::cout << "addReceiver a2" << std::endl;
	timer2.addReceiver(a2);
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);

	//=================================================
	// removeReceiver a2
	std::cout << "removeReceiver a2" << std::endl;
	timer2.removeReceiver(a2);
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);
	// removeReceiver a1
	std::cout << "removeReceiver a1" << std::endl;
	timer1.removeReceiver(a1);
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);
	//=================================================
	std::cout << "addReceiver a1" << std::endl;
	timer2.addReceiver(a1);
	std::cout << "demoTimer sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);
	timer2.removeReceiver(a1);

	cout << "end demo2Timer()" << endl;

}

