/*
 * VisitorAbstractTest.h
 *
 *  Created on: 10.01.2017
 *      Author: Gerd
 */

#ifndef INCLUDE_RECEIVERSTEST_HPP_
#define INCLUDE_RECEIVERSTEST_HPP_

#include "../Mocks/MockClassReceivers.hpp"

#include <SimplePeriodicTimer/ReceiversDemoImpl.hpp>

#include "cute.h"

#include <iostream>

#include <type_traits>

class ReceiversTest{
	using this_type = ReceiversTest;
	// Tests
	void invokeEmptyWithoutCallback();
	void invokeEmptyWithCallback();
	void addAndInvokeWithoutCallback();
	void addAndInvoke();
	void addAndRemoveInvoke();
	void changeCallback();
	void add2AndInvoke();
	void addTwiceAndInvoke();
	// Types
	using Receivers = ReceiversDemoImpl<MockClassReceivers, 3>;
public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };
		s.push_back(CUTE_SMEMFUN(DerivedTest, invokeEmptyWithoutCallback));
		s.push_back(CUTE_SMEMFUN(DerivedTest, invokeEmptyWithCallback));
		s.push_back(CUTE_SMEMFUN(DerivedTest, addAndInvokeWithoutCallback));
		s.push_back(CUTE_SMEMFUN(DerivedTest, addAndInvoke));
		s.push_back(CUTE_SMEMFUN(DerivedTest, addAndRemoveInvoke));
		s.push_back(CUTE_SMEMFUN(DerivedTest, changeCallback));
		s.push_back(CUTE_SMEMFUN(DerivedTest, add2AndInvoke));
		s.push_back(CUTE_SMEMFUN(DerivedTest, addTwiceAndInvoke));

		return s;
	}
};
inline
void ReceiversTest::invokeEmptyWithoutCallback(){
	Receivers receivers;

	ASSERTM("hasReceivers false", !receivers.hasReceiver());
	receivers.invoke();
}
inline
void ReceiversTest::invokeEmptyWithCallback(){
	Receivers receivers;
	receivers.setCallback(&MockClassReceivers::doSomething_1);

	ASSERTM("hasReceivers false", !receivers.hasReceiver());
	receivers.invoke();
}
inline
void ReceiversTest::addAndInvokeWithoutCallback(){
	Receivers receivers;
	MockClassReceivers mock("mock");
	receivers.addReceiver(mock);

	ASSERTM("hasReceivers false", !receivers.hasReceiver());
	receivers.invoke();
}
inline
void ReceiversTest::addAndInvoke(){
	Receivers receivers;
	MockClassReceivers mock("mock");
	receivers.addReceiver(mock);
	receivers.setCallback(&MockClassReceivers::doSomething_1);

	ASSERTM("hasReceivers true", receivers.hasReceiver());
	receivers.invoke();
	ASSERTM("mock not called", mock.something_1);
}

inline
void ReceiversTest::addAndRemoveInvoke(){
	Receivers receivers;
	MockClassReceivers mock("mock");
	receivers.addReceiver(mock);
	receivers.setCallback(&MockClassReceivers::doSomething_1);

	ASSERTM("hasReceivers true", receivers.hasReceiver());
	receivers.removeReceiver(mock);
	ASSERTM("hasReceivers false", !receivers.hasReceiver());
	receivers.invoke();
	ASSERTM("mock called", !mock.something_1);
}
inline
void ReceiversTest::changeCallback(){
	Receivers receivers;
	MockClassReceivers mock("mock");
	receivers.addReceiver(mock);
	receivers.setCallback(&MockClassReceivers::doSomething_1);

	ASSERTM("hasReceivers true", receivers.hasReceiver());
	receivers.invoke();
	ASSERTM("mock not called", mock.something_1);
	ASSERTM("mock called", !mock.something_2);

	receivers.setCallback(&MockClassReceivers::doSomething_2);
	receivers.invoke();
	ASSERTM("mock not called", mock.something_2);
}
inline
void ReceiversTest::add2AndInvoke(){
	Receivers receivers;
	MockClassReceivers mock1("mock1");
	MockClassReceivers mock2("mock2");
	receivers.addReceiver(mock1);
	receivers.addReceiver(mock2);
	receivers.setCallback(&MockClassReceivers::doSomething_1);

	ASSERTM("hasReceivers true", receivers.hasReceiver());
	receivers.invoke();
	ASSERTM("mock1 not called", mock1.something_1);
	ASSERTM("mock1 called", !mock1.something_2);
	ASSERTM("mock2 not called", mock2.something_1);
	ASSERTM("mock2 called", !mock2.something_2);

	receivers.setCallback(&MockClassReceivers::doSomething_2);
	receivers.invoke();
	ASSERTM("mock1 not called", mock1.something_2);
	ASSERTM("mock2 not called", mock2.something_2);
}
inline
void ReceiversTest::addTwiceAndInvoke(){
	Receivers receivers;
	MockClassReceivers mock("mock");
	receivers.addReceiver(mock);
	receivers.addReceiver(mock);
	receivers.setCallback(&MockClassReceivers::doSomething_1);

	ASSERTM("hasReceivers true", receivers.hasReceiver());
	receivers.invoke();
	ASSERTM("mock not called", mock.something_1);
}
#endif /* INCLUDE_RECEIVERSTEST_HPP_ */
