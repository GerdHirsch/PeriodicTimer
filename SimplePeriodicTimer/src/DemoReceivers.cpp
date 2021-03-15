

#include <SimplePeriodicTimer/ReceiversDemoImpl.hpp>

#include <functional>
#include <iostream>

using namespace std;
namespace{
class MyClass{
public:
	MyClass(std::string name):name(std::move(name)){}

	void doSomething_1(){
		std::cout << name << " " << __PRETTY_FUNCTION__ << std::endl;
	}
	void doSomething_2(){
		std::cout << name << " " << __PRETTY_FUNCTION__ << std::endl;
	}
	std::string name;
};

}

void demoReceivers(){
	cout << __PRETTY_FUNCTION__ << endl;

//	using MemberFunction = TrafficLight::doFlashing;
//	typedef void (TrafficLight::*pMemberFunction)();
//	using MemberFunction = void(TrafficLight::*)();

	using Receivers = ReceiversDemoImpl<MyClass, 3>;
	Receivers receivers;
	cout << "hasReceiver(): " << receivers.hasReceiver() << endl;
	cout << "receivers.invoke()" << endl;
	receivers.invoke();
	MyClass a1("a1"), a2("a2"), a3("a3");
	cout << "set a1" << endl;
	receivers.setReceiver(a1);
	cout << "hasReceiver(): " << receivers.hasReceiver() << endl;
	cout << "receivers.invoke()" << endl;
	receivers.invoke();
	cout << "setCallback(doSomething_1)" << endl;
	receivers.setCallback(&MyClass::doSomething_1);
	cout << "hasReceiver(): " << receivers.hasReceiver() << endl;
	cout << "receivers.invoke()" << endl;
	receivers.invoke();

	cout << "set a2" << endl;
	receivers.setReceiver(a2);
	receivers.setReceiver(a2);
	receivers.invoke();

	cout << "setCallback(doFlashing_2)" << endl;
	receivers.setCallback(&MyClass::doSomething_2);

	cout << "set a3" << endl;
	receivers.setReceiver(a3);
	receivers.invoke();

	cout << "remove a2" << endl;
	receivers.removeReceiver(a2);
	receivers.invoke();
}


