/*
 * MockClassTimer.hpp
 *
 *  Created on: 15.03.2021
 *      Author: Gerd
 */

#ifndef MOCKS_MOCKCLASSTIMER_HPP_
#define MOCKS_MOCKCLASSTIMER_HPP_

#include <SimplePeriodicTimer/PeriodicTimer.hpp>

class MockClassTimer{
public:
	MockClassTimer(std::string name, PeriodicTimer<MockClassTimer>& timer):name(std::move(name)), timer(&timer){}
	~MockClassTimer(){
		timer->removeReceiver(*this);
	}
	int numCalls = 0;
	void checkReentrance(){
		++numCalls;
		if(numCalls >= 3)
			timer->removeReceiver(*this);
//		std::cout << name << std::endl;
	}
	std::string name;
	PeriodicTimer<MockClassTimer>* timer;
};



#endif /* MOCKS_MOCKCLASSTIMER_HPP_ */
