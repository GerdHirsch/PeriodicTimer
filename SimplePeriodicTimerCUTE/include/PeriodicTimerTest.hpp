/*
 * SimplePeriodicTimerTest.hpp
 *
 *  Created on: 15.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_PERIODICTIMERTEST_HPP_
#define INCLUDE_PERIODICTIMERTEST_HPP_


#include "../Mocks/MockClassTimer.hpp"

#include <SimplePeriodicTimer/PeriodicTimerImpl.hpp>

#include "cute.h"

class PeriodicTimerTest{
	using this_type = PeriodicTimerTest;
	// Tests
	void checkReentrance();
	void inactiveWithoutCallback();
	void inactiveWithoutReceiver();
	void activeAfterSetCallback();
	void activeAfterAddReceiver();
	// todo timing tests
	void checkTimingConstraints();

	// Types
	using TimerRepo = DefaultTimerRepository<MockClassTimer, 3>;
	using SUT = PeriodicTimerImpl<TimerRepo>;
	using Mock = MockClassTimer;
	using Duration = std::chrono::milliseconds;
	const Duration timerDuration{5};
	const Duration testDuration{20};

public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };
		s.push_back(CUTE_SMEMFUN(DerivedTest, checkReentrance));
		s.push_back(CUTE_SMEMFUN(DerivedTest, inactiveWithoutCallback));
		s.push_back(CUTE_SMEMFUN(DerivedTest, inactiveWithoutReceiver));
		s.push_back(CUTE_SMEMFUN(DerivedTest, activeAfterSetCallback));
		s.push_back(CUTE_SMEMFUN(DerivedTest, activeAfterAddReceiver));

		s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints));

		return s;
	}
};

inline
void PeriodicTimerTest::checkTimingConstraints(){
	ASSERTM("todo checkTimingConstraints", false);
}


inline
void PeriodicTimerTest::checkReentrance(){
	SUT sut(timerDuration);
	sut.setCallback(&Mock::checkReentrance);
	Mock mock("mock", sut);
	sut.addReceiver(mock);
	std::this_thread::sleep_for(testDuration);

	ASSERTM("Three times called", mock.numCalls == 3);
}
inline
void PeriodicTimerTest::inactiveWithoutCallback(){
	SUT sut(timerDuration);
	Mock mock("mock", sut);
	sut.addReceiver(mock);
	std::this_thread::sleep_for(testDuration);

	ASSERTM("timer inactive", !sut.isThreadActive());
}
inline
void PeriodicTimerTest::inactiveWithoutReceiver(){
	SUT sut(timerDuration);
	sut.setCallback(&Mock::checkReentrance);
	std::this_thread::sleep_for(testDuration);

	ASSERTM("timer inactive", !sut.isThreadActive());
}
inline
void PeriodicTimerTest::activeAfterSetCallback(){
	SUT sut(timerDuration);
	Mock mock("mock", sut);
	sut.addReceiver(mock);
	ASSERTM("timer inactive", !sut.isThreadActive());
	sut.setCallback(&Mock::checkReentrance);
	ASSERTM("timer active", sut.isThreadActive());
	sut.removeReceiver(mock);
	std::this_thread::sleep_for(testDuration);
	ASSERTM("timer inactive", !sut.isThreadActive());
}
inline
void PeriodicTimerTest::activeAfterAddReceiver(){
	SUT sut(timerDuration);
	sut.setCallback(&Mock::checkReentrance);
	ASSERTM("timer inactive", !sut.isThreadActive());

	Mock mock("mock", sut);
	sut.addReceiver(mock);
	ASSERTM("timer active", sut.isThreadActive());
	sut.removeReceiver(mock);
	std::this_thread::sleep_for(testDuration);
	ASSERTM("timer inactive", !sut.isThreadActive());
}
#endif /* INCLUDE_PERIODICTIMERTEST_HPP_ */
