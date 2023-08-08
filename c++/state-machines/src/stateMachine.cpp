/*
 *  stateMachine.cpp
 *  sm
 *
 *  Created by Scott Gustafson on 5/2/11.
 *  Copyright 2011 Garlic Software LLC. All rights reserved.
 *
 */

#include "stateMachine.h"

stateMachine::stateMachine(void) {
	m_currentState = nullptr;
}

stateMachine::~stateMachine(void) {
	while (!m_stateList.empty()) {
		state *aState = m_stateList.front();
		m_stateList.pop_front();
		delete aState;
	}
}

void stateMachine::advance(void) {
	if (m_currentState == nullptr) {
		return;
	}
	m_currentState->performAction();
	m_currentState = m_currentState->nextState();
}

void stateMachine::run(void) {
	if (m_currentState == nullptr) {
		return;
	}
	if (m_currentState->canAdvance()) {
		advance();
	}
}