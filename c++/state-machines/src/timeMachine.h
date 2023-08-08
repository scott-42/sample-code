/*
 *  timeMachine.h
 *  sm
 *
 *  Created by Scott Gustafson on 5/2/11.
 *  Copyright 2011 Garlic Software LLC. All rights reserved.
 *
 */


// One state machine prints the wall clock time to stdout every 1.4 seconds in HH:MM:SS.mm format,
// where HH = hours since start of day (0-23), MM = minute in current hour (0-59), SS = seconds in 
// current minute (0-59), and mm = milliseconds in current second (00-99).


#include "stateMachine.h"

class timeMachine : public stateMachine {
	public:
		timeMachine(void);
};