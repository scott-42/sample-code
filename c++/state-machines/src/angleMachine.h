/*
 *  angleMachine.h
 *  sm
 *
 *  Created by Scott Gustafson on 5/2/11.
 *  Copyright 2011 Garlic Software LLC. All rights reserved.
 *
 */


// The other state machine prints the points around the circumference of a unit circle 
// (radius = 1) to stderr every 1.2 seconds.  The starting angle = zero and the angle is 
// incremented each time it is printed according to the following schedule: 1 degree, 4 
// degrees, 13 degrees, 7 degrees, 20 degrees (after incrementing by 20, wrap around and 
// start again at 1.)  The output should be formatted as: "x, y, <time>", where <time> 
// can have any format provided that it has at least millisecond resolution.  The x and 
// y coordinates can be any format you choose.


#include "stateMachine.h"

class angleMachine : public stateMachine {
	protected:
		int m_angle;

		virtual void advance(void);

	public:
		angleMachine(void);
};