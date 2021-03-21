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
	MockClassTimer(std::string name, SimplePeriodicTimer::PeriodicTimer<MockClassTimer>& timer)
	:
		numCalls(0),
		name(std::move(name)),
		timer(&timer){}

	~MockClassTimer(){
		timer->removeReceiver(*this);
	}
	std::size_t numCalls = 0;
	const std::size_t numReentranceRuns{3};

	void checkReentrance(){
		++numCalls;
		if(numCalls >= numReentranceRuns){
			timer->removeReceiver(*this);
		}
	}

	decltype(std::chrono::steady_clock::now()) start;
	decltype(std::chrono::steady_clock::now()) end;
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
	void checkShortTimingConstraints(){
		if(numCalls == 0)
			start = std::chrono::steady_clock::now();
		++numCalls;
		if(numCalls >= numTimingRuns){
			end = std::chrono::steady_clock::now();
			timer->removeReceiver(*this);
		}
	}
	std::string name;
	SimplePeriodicTimer::PeriodicTimer<MockClassTimer>* timer;
};



#endif /* MOCKS_MOCKCLASSTIMER_HPP_ */
