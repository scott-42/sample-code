#ifndef STATE_H
#define STATE_H

/*
 *  state.h
 *  sm
 *
 *  Created by Scott Gustafson on 5/2/11.
 *  Copyright 2011 Garlic Software LLC. All rights reserved.
 *
 */

class state {
	protected:
		state *m_nextState;
		
	public:
		state(void);
		
		void setNextState(state *nextState);
		state* nextState(void) {return m_nextState;}

		virtual void performAction(void) {;}
		virtual bool canAdvance(void) {return false;}
};

#endif