#ifndef RECEIVERSDEMOIMPL_HPP_
#define RECEIVERSDEMOIMPL_HPP_

#include <cstddef> // size_t

template<class Receiver_, std::size_t numReceivers>
class ReceiversDemoImpl{
public:
	using Receiver = Receiver_;
	using MemberFunction = void(Receiver::*)();

	ReceiversDemoImpl()
	:
		function(nullptr)
	{
		for(auto& receiver : receivers) receiver = nullptr;
	}

	void setReceiver(Receiver& newReceiver){
		// no more space available
		if(currentNumReceivers == numReceivers) return;

		// no duplicates
		for(auto receiver : receivers)
			if(receiver == &newReceiver) return;
		// check for a place to put the new receiver
		for(auto& receiver : receivers){
			if(receiver == nullptr) {
				receiver = &newReceiver;
				++currentNumReceivers;
				break;
			}
		}
	}
	void removeReceiver(Receiver& oldReceiver){
		for(auto& receiver : receivers){
			if(receiver == &oldReceiver){
				receiver = nullptr;
				--currentNumReceivers;
			}
		}

	}
	bool hasReceiver() const {
		return currentNumReceivers != 0 && function != nullptr;
	}
	void setCallback(MemberFunction function){
		this->function = function;
	}
	void invoke(){
		for(auto receiver : receivers){
			if(receiver != nullptr && function != nullptr) (receiver->*function)();
		}
	}
private:
	MemberFunction function;
	Receiver* receivers[numReceivers];
	std::size_t currentNumReceivers = 0;
};



#endif /* RECEIVERSDEMOIMPL_HPP_ */
