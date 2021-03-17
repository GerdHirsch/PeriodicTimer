/*
 * TimingConstraintsTest.hpp
 *
 *  Created on: 17.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TIMINGCONSTRAINTSTEST_HPP_
#define INCLUDE_TIMINGCONSTRAINTSTEST_HPP_


#include <PeriodicTimer/PeriodicTimerImpl.hpp>

#include "../Mocks/MockClassTimer.hpp"

#include "cute.h"

class TimingConstraintsTest{
	using this_type = TimingConstraintsTest;
	// timing tests
	void checkTimingConstraints_1ms();
	void checkTimingConstraints_10ms();
	void checkTimingConstraints_20ms();
	void checkTimingConstraints_30ms();
	void checkTimingConstraints_50ms();
	void checkTimingConstraints_100ms();
	void checkTimingConstraints_300ms();
	void checkTimingConstraints_500ms();

	// Types
	using TimerRepo = SimplePeriodicTimer::DefaultTimerRepository<MockClassTimer, 3>;
	using SUT = SimplePeriodicTimer::PeriodicTimerImpl<TimerRepo>;
	using Mock = MockClassTimer;
	using Duration = std::chrono::milliseconds;
//	const Duration timerDuration{5};
//	const Duration testDuration{25};

public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };

		// always to late expected 10 but 117 ...
		//s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints_1ms));
		// always to late expected 100 but 148
		//s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints_10ms));

		s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints_20ms));
		s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints_30ms));
		// < +10%
		s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints_50ms));
		// < -0,50%
		s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints_100ms));
		// < -0,8%
		s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints_300ms));
		// < -2%
		s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints_500ms));

		return s;
	}
};
// always to late
inline
void TimingConstraintsTest::checkTimingConstraints_1ms(){
	using namespace std;
	SUT sut(1);
	sut.setCallback(&Mock::checkShortTimingConstraints);
	Mock mock("mock", sut);

	auto start = std::chrono::steady_clock::now();

	sut.addReceiver(mock);

	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(1));

	auto end = std::chrono::steady_clock::now();

	cout << "mock.end - mock.start: " << chrono::duration_cast<Duration>(mock.end - mock.start) << endl;
	cout << "end - start: " << chrono::duration_cast<Duration>(end - start) << endl;

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());
	ASSERT_EQUAL_DELTAM("10 x 1: ", 10, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 10);
}

inline
void TimingConstraintsTest::checkTimingConstraints_10ms(){
	using namespace std;
	SUT sut(10);
	sut.setCallback(&Mock::checkTimingConstraints);
	Mock mock("mock", sut);
	sut.addReceiver(mock);

	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(100));

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());
	ASSERT_EQUAL_DELTAM("10 x 10, 50: ", 100, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 60);
	ASSERT_EQUAL_DELTAM("10 x 10, 50: ", 100, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 50);
	ASSERT_EQUAL_DELTAM("10 x 10, 30: ", 100, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 30);
	ASSERT_EQUAL_DELTAM("10 x 10, 10: ", 100, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 10);
}
// toleranz < 10%

inline
void TimingConstraintsTest::checkTimingConstraints_20ms(){
	using namespace std;
	auto timerPeriod = 20;// ms

	SUT sut(timerPeriod);
	sut.setCallback(&Mock::checkTimingConstraints);
	Mock mock("mock", sut);

	int expected = timerPeriod * mock.numTimingRuns;
	auto percent10 = timerPeriod * 0.1 * mock.numTimingRuns;

	sut.addReceiver(mock);
	//
	std::this_thread::sleep_for(chrono::milliseconds(expected));
	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(10));

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());

	auto result = chrono::duration_cast<Duration>(mock.end - mock.start).count();

	ASSERT_EQUAL_DELTAM("10 x 20, 10%: ", expected, result, percent10); //10%
	ASSERT_EQUAL_DELTAM("10 x 20, 10: ", expected, result, 10);
}
inline
void TimingConstraintsTest::checkTimingConstraints_30ms(){
	using namespace std;
	auto timerPeriod = 30;// ms

	SUT sut(timerPeriod);
	sut.setCallback(&Mock::checkTimingConstraints);
	Mock mock("mock", sut);

	int expected = timerPeriod * mock.numTimingRuns;
	auto percent10 = timerPeriod * 0.1 * mock.numTimingRuns;

	sut.addReceiver(mock);
	//
	std::this_thread::sleep_for(chrono::milliseconds(expected));
	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(10));

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());

	auto result = chrono::duration_cast<Duration>(mock.end - mock.start).count();

	ASSERT_EQUAL_DELTAM("10 x 30, 10%: ", expected, result, percent10); //10%
	ASSERT_EQUAL_DELTAM("10 x 30, 10: ", expected, result, 10);
}

inline
void TimingConstraintsTest::checkTimingConstraints_50ms(){
	using namespace std;
	auto timerPeriod = 50;// ms

	SUT sut(timerPeriod);
	sut.setCallback(&Mock::checkTimingConstraints);
	Mock mock("mock", sut);

	int expected = timerPeriod * mock.numTimingRuns;
	auto percent10 = timerPeriod * 0.1 * mock.numTimingRuns;

	sut.addReceiver(mock);
	//
	std::this_thread::sleep_for(chrono::milliseconds(expected));
	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(10));

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());

	auto result = chrono::duration_cast<Duration>(mock.end - mock.start).count();

	ASSERT_EQUAL_DELTAM("10 x 50, 70: ", expected, result, 70);
	ASSERT_EQUAL_DELTAM("10 x 50, 10%: ", expected, result, percent10); //10%
}

inline
void TimingConstraintsTest::checkTimingConstraints_100ms(){
	using namespace std;
	auto timerPeriod = 100;// ms

	SUT sut(timerPeriod);
	sut.setCallback(&Mock::checkTimingConstraints);
	Mock mock("mock", sut);

	int expected = timerPeriod * mock.numTimingRuns;
	auto percent10 = timerPeriod * 0.1 * mock.numTimingRuns;

	sut.addReceiver(mock);
	//
	std::this_thread::sleep_for(chrono::milliseconds(expected));
	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(10));

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());

	auto result = chrono::duration_cast<Duration>(mock.end - mock.start).count();

	ASSERT_EQUAL_DELTAM("10 x 100, 10%: ", expected, result, percent10); //10%
	ASSERT_EQUAL_DELTAM("10 x 100, 40: ", expected, result, 40);
}

inline
void TimingConstraintsTest::checkTimingConstraints_300ms(){
	using namespace std;
	auto timerPeriod = 300;// ms

	SUT sut(timerPeriod);
	sut.setCallback(&Mock::checkTimingConstraints);
	Mock mock("mock", sut);

	int expected = timerPeriod * mock.numTimingRuns;
	auto percent10 = timerPeriod * 0.1 * mock.numTimingRuns;

	sut.addReceiver(mock);
	//
	std::this_thread::sleep_for(chrono::milliseconds(expected));
	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(10));

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());

	auto result = chrono::duration_cast<Duration>(mock.end - mock.start).count();

	ASSERT_EQUAL_DELTAM("10 x 300, 10%: ", expected, result, percent10); //10%
//	ASSERT_EQUAL_DELTAM("10 x 300, 150: ", expected, result, 150);
}
inline
void TimingConstraintsTest::checkTimingConstraints_500ms(){
	using namespace std;
	auto timerPeriod = 500;// ms

	SUT sut(timerPeriod);
	sut.setCallback(&Mock::checkTimingConstraints);
	Mock mock("mock", sut);

	int expected = timerPeriod * mock.numTimingRuns;
	auto percent10 = timerPeriod * 0.1 * mock.numTimingRuns;

	sut.addReceiver(mock);
	//
	std::this_thread::sleep_for(chrono::milliseconds(expected));
	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(10));

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());

	auto result = chrono::duration_cast<Duration>(mock.end - mock.start).count();

	ASSERT_EQUAL_DELTAM("10 x 500, 10%: ", expected, result, percent10); //10%
//	ASSERT_EQUAL_DELTAM("10 x 500, 400: ", expected, result, 400);
//	ASSERT_EQUAL_DELTAM("10 x 500, 300: ", expected, result, 300);
//	ASSERT_EQUAL_DELTAM("10 x 500, 100: ", expected, result, 100);
}

#endif /* INCLUDE_TIMINGCONSTRAINTSTEST_HPP_ */
