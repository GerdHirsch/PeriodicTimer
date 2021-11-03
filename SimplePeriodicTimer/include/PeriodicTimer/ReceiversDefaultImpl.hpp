#ifndef RECEIVERSDEMOIMPL_HPP_
#define RECEIVERSDEMOIMPL_HPP_

#include <cstddef> // size_t

namespace SimplePeriodicTimer{

template<class Receiver_, std::size_t maxReceivers>
class ReceiversDemoImpl{
public:
	using Receiver = Receiver_;
	using MemberFunction = void(Receiver::*)();
	// Refactoring neccessary
	// Rename: ReceiversDefaultImpl
	ReceiversDemoImpl()
	:
		function(nullptr)
	{
		for(auto& receiver : receivers) receiver = nullptr;
	}

	void addReceiver(Receiver& newReceiver){
		// Refactoring neccessary
		// bool isFull(){ return currentNumReceivers == maxReceivers;}
		// no more space available
		if(currentNumReceivers == maxReceivers) return;

		// Refactoring neccessary
		// bool isAlreadyAdded(Receiver& newReceiver){ see no duplicates }
		// no duplicates
		for(auto receiver : receivers)
			if(receiver == &newReceiver) return;
		// Refactoring neccessary
		// void insertReceiver(Receiver& newReceiver){ see check for a place to put }
		// check for a place to put the new receiver
		for(auto& receiver : receivers){
			if(receiver == nullptr) {
				receiver = &newReceiver;
				++currentNumReceivers;
				break;
			}
		}
	}
	void setCallback(MemberFunction function){
		this->function = function;
	}
	void removeReceiver(Receiver& oldReceiver){
		for(auto& receiver : receivers){
			if(receiver == &oldReceiver){
				receiver = nullptr;
				--currentNumReceivers;
			}
		}
	}
	// Refactoring neccessary
	// bool canBeInvoked() const { return hasReceiver() && hasCallback(); }
	bool canBeInvoked() const {
		return currentNumReceivers != 0 && function != nullptr;
	}
	bool hasReceiver() const {
		return currentNumReceivers != 0;
	}
	// Refactoring neccessary
	// bool hasCallback() const{ ...}
	bool hasCallback(){
		return function != nullptr;
	}


	std::size_t getCurrentNumberOfReceivers(){
		return currentNumReceivers;
	}
	void invoke(){
		if(function == nullptr) return;

		for(auto receiver : receivers){
			if(receiver != nullptr) (receiver->*function)();
		}
	}
private:
	MemberFunction function = nullptr;
	Receiver* receivers[maxReceivers];
	std::size_t currentNumReceivers = 0;
};

} //namespace SimplePeriodicTimer


#endif /* RECEIVERSDEMOIMPL_HPP_ */
