/*
 * database.h
 *
 *  Created on: Jun 13, 2018
 *      Author: scott
 * Copyright © 2018 R. Scott Gustafson. All rights reserved.
*/

#ifndef DATABASE_H_
#define DATABASE_H_

#include <map>
#include "phoneNumber.h"

using namespace std;

class database {
private:
	// Assumption: call record lengths are in minutes and are generally short,
	// less than a day per call (60 minutes/hour * 24 hours/day = 1440 minutes/day)
	// using a short to represent that small number
	multimap<phoneNumber, unsigned short> callRecords;

public:
	database();
	virtual ~database();

	void addRecord(unsigned long number, unsigned short minutes);
	void printTopBusy(unsigned int N) const;

#if defined(TEST)
	friend class database_test;
#endif
};

#endif /* DATABASE_H_ */
