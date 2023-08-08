/*
 *  angleMachine.cpp
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
#include <math.h>
#include "angleMachine.h"

const float timeIncrement = 1.2;
const int numberOfStates = 5;

class angleMachineState : public state {
	protected:
		double m_referenceTime;
		int m_angleIncrement;

	public:
		angleMachineState(angleMachineState *previousState = NULL, int angleIncrement = 0);
		
		virtual int performAction(int currentAngle);
		virtual bool canAdvance(void);	
};

angleMachineState::angleMachineState(angleMachineState *previousState, int angleIncrement) {
	if (previousState == NULL) {
		// keep track of the time we started up
		timeval currentTime;
		int error = gettimeofday(&currentTime, NULL);
		if (error != 0) {
			std::cerr << "Error getting the time in angleMachineState::angleMachineState:" << std::endl;
			throw;
		}
		m_referenceTime = currentTime.tv_sec + currentTime.tv_usec / 1000000.0;
	} else {
		m_referenceTime = previousState->m_referenceTime + timeIncrement;
	}
	
	m_angleIncrement = angleIncrement;
}

int angleMachineState::performAction(int currentAngle) {
	m_referenceTime += (timeIncrement * (float)numberOfStates);
	
	timeval currentTime;
	int error = gettimeofday(&currentTime, NULL);
	if (error != 0) {
		std::cerr << "Error getting the time in angleMachineState::performAction:" << std::endl;
		throw;
	}
	
	tm *parts = localtime(&currentTime.tv_sec);
	
	double angle = (float)currentAngle * (M_PI / 180.0);	// convert degrees to radians
	
	// calculate the x,y coordinates of a unit circle (radius = 1)
	double x = cos(angle);
	double y = sin(angle);
	
	std::cerr << std::fixed << std::setprecision(5) << x << ", ";
	std::cerr << std::fixed << std::setprecision(5) << y << ", ";
	
	std::cerr << std::setw(2) << std::setfill('0') << parts->tm_hour << ':';
	std::cerr << std::setw(2) << std::setfill('0') << parts->tm_min << ':';
	std::cerr << std::setw(2) << std::setfill('0') << parts->tm_sec << '.';
	std::cerr << std::setw(2) << std::setfill('0') << (int)(((float)currentTime.tv_usec / 1000000.0) * 100.0);
	std::cerr << std::endl;
	
	currentAngle += m_angleIncrement;
	if (currentAngle >= 360) {
		currentAngle -= 360;
	}
	
	return currentAngle;
}

bool angleMachineState::canAdvance(void) {
	timeval currentTime;
	int error = gettimeofday(&currentTime, NULL);
	if (error != 0) {
		std::cerr << "Error getting the time in angleMachineState::canAdvance:" << std::endl;
		throw;
	}
	
	double testTime = currentTime.tv_sec + currentTime.tv_usec / 1000000.0;
	if (testTime > m_referenceTime + timeIncrement) {
		return true;
	}
	return false;
}


class angleMachineState1 : public angleMachineState {
	public:
		angleMachineState1(angleMachineState *previousState);
};

angleMachineState1::angleMachineState1(angleMachineState *previousState) : angleMachineState(previousState, 1) {;}

class angleMachineState2 : public angleMachineState {
	public:
		angleMachineState2(angleMachineState *previousState);
};

angleMachineState2::angleMachineState2(angleMachineState *previousState) : angleMachineState(previousState, 4) {;}

class angleMachineState3 : public angleMachineState {
	public:
		angleMachineState3(angleMachineState *previousState);
};

angleMachineState3::angleMachineState3(angleMachineState *previousState) : angleMachineState(previousState, 13) {;}

class angleMachineState4 : public angleMachineState {
	public:
		angleMachineState4(angleMachineState *previousState);
};

angleMachineState4::angleMachineState4(angleMachineState *previousState) : angleMachineState(previousState, 7) {;}

class angleMachineState5 : public angleMachineState {
	public:
		angleMachineState5(angleMachineState *previousState);
};

angleMachineState5::angleMachineState5(angleMachineState *previousState) : angleMachineState(previousState, 20) {;}

angleMachine::angleMachine(void) {
	m_angle = 0;
	
	angleMachineState1 *state1 = new angleMachineState1(NULL);
	m_stateList.push_back(state1);
	m_currentState = state1;

	angleMachineState2 *state2 = new angleMachineState2(state1);
	m_stateList.push_back(state2);
	state1->setNextState(state2);

	angleMachineState3 *state3 = new angleMachineState3(state2);
	m_stateList.push_back(state3);
	state2->setNextState(state3);

	angleMachineState4 *state4 = new angleMachineState4(state3);
	m_stateList.push_back(state4);
	state3->setNextState(state4);

	angleMachineState5 *state5 = new angleMachineState5(state4);
	m_stateList.push_back(state5);
	state4->setNextState(state5);

	state5->setNextState(state1);
}

void angleMachine::advance(void) {
	if (m_currentState == NULL) {
		return;
	}
	m_angle = dynamic_cast<angleMachineState*>(m_currentState)->performAction(m_angle);
	m_currentState = m_currentState->nextState();
}

