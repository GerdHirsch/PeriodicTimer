/*
 * MockClass.hpp
 *
 *  Created on: 15.03.2021
 *      Author: Gerd
 */

#ifndef MOCKS_MOCKCLASSRECEIVERS_HPP_
#define MOCKS_MOCKCLASSRECEIVERS_HPP_

#include <string>

class MockClassReceivers{
public:
	MockClassReceivers(std::string name):name(std::move(name)){}

	int something_1 = 0;
	void doSomething_1(){
//		std::cout << name << " " << __PRETTY_FUNCTION__ << std::endl;
		++something_1;
	}

	bool something_2 = false;
	void doSomething_2(){
//		std::cout << name << " " << __PRETTY_FUNCTION__ << std::endl;
		something_2 = true;
	}
	std::string name;
};

#endif /* MOCKS_MOCKCLASSRECEIVERS_HPP_ */
