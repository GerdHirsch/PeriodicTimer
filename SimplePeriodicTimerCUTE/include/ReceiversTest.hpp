/*
 * VisitorAbstractTest.h
 *
 *  Created on: 10.01.2017
 *      Author: Gerd
 */

#ifndef INCLUDE_RECEIVERSTEST_HPP_
#define INCLUDE_RECEIVERSTEST_HPP_

#include <PeriodicTimer/ReceiversDefaultImpl.hpp>

#include "../Mocks/MockClassReceivers.hpp"

#include "cute.h"

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
	using SUT = ReceiversDemoImpl<MockClassReceivers, 3>;
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
	SUT receivers;

	ASSERTM("hasReceivers false", !receivers.hasReceiver());
	receivers.invoke();
}
inline
void ReceiversTest::invokeEmptyWithCallback(){
	SUT receivers;
	receivers.setCallback(&MockClassReceivers::doSomething_1);

	ASSERTM("hasReceivers false", !receivers.hasReceiver());
	receivers.invoke();
}
inline
void ReceiversTest::addAndInvokeWithoutCallback(){
	SUT receivers;
	MockClassReceivers mock("mock");
	receivers.addReceiver(mock);

	ASSERTM("hasReceivers false", !receivers.hasReceiver());
	receivers.invoke();
}
inline
void ReceiversTest::addAndInvoke(){
	SUT receivers;
	MockClassReceivers mock("mock");
	receivers.addReceiver(mock);
	receivers.setCallback(&MockClassReceivers::doSomething_1);

	ASSERTM("hasReceivers true", receivers.hasReceiver());
	receivers.invoke();
	ASSERTM("mock not called", mock.something_1 == 1);
}

inline
void ReceiversTest::addAndRemoveInvoke(){
	SUT receivers;
	MockClassReceivers mock("mock");
	receivers.setCallback(&MockClassReceivers::doSomething_1);

	receivers.addReceiver(mock);
	ASSERTM("hasReceivers true", receivers.hasReceiver());
	ASSERTM("numReceivers == 1", receivers.getCurrentNumberOfReceivers() == 1);

	receivers.removeReceiver(mock);
	ASSERTM("hasReceivers false", !receivers.hasReceiver());
	ASSERTM("numReceivers == 0", receivers.getCurrentNumberOfReceivers() == 0);

	receivers.invoke();
	ASSERTM("mock called", mock.something_1 == 0);
}
inline
void ReceiversTest::changeCallback(){
	SUT receivers;
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
	SUT receivers;
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
	SUT receivers;
	MockClassReceivers mock("mock");
	receivers.addReceiver(mock);
	receivers.addReceiver(mock);
	receivers.setCallback(&MockClassReceivers::doSomething_1);

	ASSERTM("hasReceivers true", receivers.hasReceiver());
	receivers.invoke();
	ASSERTM("mock not called", mock.something_1 == 1);
	receivers.invoke();
	ASSERTM("mock not called", mock.something_1 == 2);
}
#endif /* INCLUDE_RECEIVERSTEST_HPP_ */
