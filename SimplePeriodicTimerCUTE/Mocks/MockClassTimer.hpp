/*
 * MockClassTimer.hpp
 *
 *  Created on: 15.03.2021
 *      Author: Gerd
 */

#ifndef MOCKS_MOCKCLASSTIMER_HPP_
#define MOCKS_MOCKCLASSTIMER_HPP_

#include <PeriodicTimer/PeriodicTimer.hpp>
#include <cstddef>

class MockClassTimer{
public:
	MockClassTimer(std::string name, SimplePeriodicTimer::PeriodicTimer<MockClassTimer>& timer):name(std::move(name)), timer(&timer){}
	~MockClassTimer(){
		timer->removeReceiver(*this);
	}
	std::size_t numCalls = 0;
	const std::size_t numReentranceRuns{10};

	decltype(std::chrono::steady_clock::now()) start;
	decltype(std::chrono::steady_clock::now()) end;

	void checkReentrance(){
		++numCalls;
		if(numCalls >= numReentranceRuns){
			timer->removeReceiver(*this);
		}
	}
	const std::size_t numTimingRuns{10};
	void checkTimingConstraints(){
		if(numCalls == 0)
			start = std::chrono::steady_clock::now();
		++numCalls;
		if(numCalls >= numTimingRuns){
			timer->removeReceiver(*this);
			end = std::chrono::steady_clock::now();
		}
	}
	std::string name;
	SimplePeriodicTimer::PeriodicTimer<MockClassTimer>* timer;
};



#endif /* MOCKS_MOCKCLASSTIMER_HPP_ */
