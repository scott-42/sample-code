/*
 *  timeMachine.cpp
 *  sm
 *
 *  Created by Scott Gustafson on 5/2/11.
 *  Copyright 2011 Garlic Software LLC. All rights reserved.
 *
 */

#include <iostream>
#include <iomanip>
#include <ios>
#include <sys/time.h>
#include <time.h>
#include "timeMachine.h"

const float timeIncrement = 1.4;

class timeMachineState1 : public state {
	protected:
		double m_referenceTime;

	public:
		timeMachineState1(void);
		
		virtual void performAction(void);
		virtual bool canAdvance(void);	
};

timeMachineState1::timeMachineState1(void) {
	// keep track of the time we started up
	timeval currentTime;
	int error = gettimeofday(&currentTime, NULL);
	if (error != 0) {
		std::cerr << "Error getting the time in timeMachineState1::timeMachineState1:" << std::endl;
		throw;
	}
	m_referenceTime = currentTime.tv_sec + currentTime.tv_usec / 1000000.0;
}

void timeMachineState1::performAction(void) {
	m_referenceTime += timeIncrement;

	timeval currentTime;
	int error = gettimeofday(&currentTime, NULL);
	if (error != 0) {
		std::cerr << "Error getting the time in timeMachineState1::performAction:" << std::endl;
		throw;
	}
	
	tm *parts = localtime(&currentTime.tv_sec);
	
	std::cout << std::setw(2) << std::setfill('0') << parts->tm_hour << ':';
	std::cout << std::setw(2) << std::setfill('0') << parts->tm_min << ':';
	std::cout << std::setw(2) << std::setfill('0') << parts->tm_sec << '.';
	std::cout << std::setw(2) << std::setfill('0') << (int)(((float)currentTime.tv_usec / 1000000.0) * 100.0);
	std::cout << std::endl;
}

bool timeMachineState1::canAdvance(void) {
	timeval currentTime;
	int error = gettimeofday(&currentTime, NULL);
	if (error != 0) {
		std::cerr << "Error getting the time in timeMachineState1::canAdvance:" << std::endl;
		throw;
	}
	
	double testTime = currentTime.tv_sec + currentTime.tv_usec / 1000000.0;
	if (testTime > m_referenceTime + timeIncrement) {
		return true;
	}
	return false;
}

timeMachine::timeMachine(void) {
	timeMachineState1 *state1 = new timeMachineState1;
	m_stateList.push_back(state1);
	state1->setNextState(state1);
	m_currentState = state1;
}
