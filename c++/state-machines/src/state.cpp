/*
 *  state.cpp
 *  sm
 *
 *  Created by Scott Gustafson on 5/2/11.
 *  Copyright 2011 Garlic Software LLC. All rights reserved.
 *
 */

#include <stddef.h>
#include "state.h"

state::state(void) {
	m_nextState = nullptr;
}

void state::setNextState(state *nextState) {
	m_nextState = nextState;
}