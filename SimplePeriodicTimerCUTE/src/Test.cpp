

#include "../include/ReceiversTest.hpp"
#include "../include/PeriodicTimerTest.hpp"
#include "../include/TimingConstraintsTest.hpp"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


void thisIsATest() {
	ASSERTM("start writing tests", false);	
}

void runAllTests(int argc, char const *argv[]) {

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> listener(xmlfile.out);
//	auto runner = cute::makeRunner(lis, argc, argv);
//	bool success = runner(s, "AllTests");

//	cute::makeRunner(listener,argc,argv)(ReceiversTest::make_suite(), "Receiver");
//	cute::makeRunner(listener,argc,argv)(PeriodicTimerTest::make_suite(), "PeriodicTimer");
	cute::makeRunner(listener,argc,argv)(TimingConstraintsTest::make_suite(), "TimingConstraints");

}

int main(int argc, char const *argv[]) {
    runAllTests(argc, argv);
}
