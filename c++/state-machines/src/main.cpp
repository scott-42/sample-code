// Copyright 2011 Garlic Software LLC. All rights reserved.

#include <iostream>
#include "timeMachine.h"
#include "angleMachine.h"

int main (int argc, char * const argv[]) {
    
	// create two state machines
	try {
		timeMachine machine1;
		angleMachine machine2;
		
		while (true) {
			machine1.run();
			machine2.run();
		}
	}
	catch (...) {
		std::cerr << "Exception caught, exiting app." << std::endl;
	}
	
    return 0;
}
