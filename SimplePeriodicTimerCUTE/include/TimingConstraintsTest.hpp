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
	void checkTimingConstraints_50ms();
	void checkTimingConstraints_100ms();
	void checkTimingConstraints_300ms();
	void checkTimingConstraints_500ms();

	// Types
	using TimerRepo = SimplePeriodicTimer::DefaultTimerRepository<MockClassTimer, 3>;
	using SUT = SimplePeriodicTimer::PeriodicTimerImpl<TimerRepo>;
	using Mock = MockClassTimer;
	using Duration = std::chrono::milliseconds;
	const Duration timerDuration{5};
	const Duration testDuration{25};

public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };

		// always to late expected 10 but 117 ...
		//s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints_1ms));
		// always to late expected 100 but 148
		//s.push_back(CUTE_SMEMFUN(DerivedTest, checkTimingConstraints_10ms));

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

inline
void TimingConstraintsTest::checkTimingConstraints_50ms(){
	using namespace std;
	SUT sut(50);

	Mock mock("mock", sut);
	sut.addReceiver(mock);
	sut.setCallback(&Mock::checkTimingConstraints);

	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(500));

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());

	int expected = 500;
	ASSERT_EQUAL_DELTAM("10 x 50, 50: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 50);
	ASSERT_EQUAL_DELTAM("10 x 50, 40: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 40);
	// outside toleranz
	//	ASSERT_EQUAL_DELTAM("10 x 50, 10: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 10);
}
inline
void TimingConstraintsTest::checkTimingConstraints_100ms(){
	using namespace std;
	SUT sut(100);
	sut.setCallback(&Mock::checkTimingConstraints);
	Mock mock("mock", sut);
	sut.addReceiver(mock);

	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(300));

	cout << "end - start: " << chrono::duration_cast<Duration>(mock.end - mock.start) << endl;

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());

	int expected = 1000;
	ASSERT_EQUAL_DELTAM("10 x 100, 50: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 40);
//	ASSERT_EQUAL_DELTAM("10 x 100, 30: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 30);
//	ASSERT_EQUAL_DELTAM("10 x 100, 10: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 10);
}
inline
void TimingConstraintsTest::checkTimingConstraints_300ms(){
	using namespace std;
	SUT sut(300);
	sut.setCallback(&Mock::checkTimingConstraints);
	Mock mock("mock", sut);
	sut.addReceiver(mock);

	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(500));

	cout << "end - start: " << chrono::duration_cast<Duration>(mock.end - mock.start) << endl;

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());

	int expected = 3000;
	ASSERT_EQUAL_DELTAM("10 x 300, 500: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 500);
	ASSERT_EQUAL_DELTAM("10 x 300, 300: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 300);
//	ASSERT_EQUAL_DELTAM("10 x 300, 100: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 100);
}
inline
void TimingConstraintsTest::checkTimingConstraints_500ms(){
	using namespace std;
	SUT sut(500);
	sut.setCallback(&Mock::checkTimingConstraints);
	Mock mock("mock", sut);
	sut.addReceiver(mock);

	while(sut.isThreadActive())
		std::this_thread::sleep_for(chrono::milliseconds(500));

	cout << "end - start: " << chrono::duration_cast<Duration>(mock.end - mock.start) << endl;

	ASSERT_EQUALM("times called", mock.numTimingRuns, mock.numCalls);
	ASSERTM("timer inactive", !sut.isThreadActive());

	int expected = 5000;
	ASSERT_EQUAL_DELTAM("10 x 500, 500: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 500);
//	ASSERT_EQUAL_DELTAM("10 x 500, 400: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 400);
//	ASSERT_EQUAL_DELTAM("10 x 500, 300: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 300);
//	ASSERT_EQUAL_DELTAM("10 x 500, 100: ", expected, chrono::duration_cast<Duration>(mock.end - mock.start).count(), 100);
}



#endif /* INCLUDE_TIMINGCONSTRAINTSTEST_HPP_ */
