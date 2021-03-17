#ifndef PERIODICTIMER_HPP_
#define PERIODICTIMER_HPP_

namespace SimplePeriodicTimer{

template<class Receiver>
class PeriodicTimer{
public:
	using MemberFunction = void(Receiver::*)();
	virtual void addReceiver(Receiver&)=0;
	virtual void removeReceiver(Receiver&)=0;
	virtual void setCallback(MemberFunction function)=0;
	virtual void setIntervalDuration(unsigned long long intervalDuration)=0;
};

} // namespace SimplePeriodicTimer
#endif /* PERIODICTIMER_HPP_ */
