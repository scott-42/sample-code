#ifndef STATEMACHINE_H
#define STATEMACHINE_H

/*
 *  stateMachine.h
 *  sm
 *
 *  Created by Scott Gustafson on 5/2/11.
 *  Copyright 2011 Garlic Software LLC. All rights reserved.
 *
 */

#include <list>
#include "state.h"

class stateMachine {
	protected:
		state* m_currentState;
		std::list<state*> m_stateList;
	
		virtual void advance(void);
	
	public:
		stateMachine(void);
		virtual ~stateMachine(void);
		
		void run(void);
};

#endif