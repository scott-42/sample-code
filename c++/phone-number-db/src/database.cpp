/*
 * database.cpp
 *
 *  Created on: Jun 13, 2018
 *      Author: scott
 * Copyright © 2018 R. Scott Gustafson. All rights reserved.
 */

#include <iostream>
#include "database.h"

using namespace std;

database::database() {

}

database::~database() {

}

// create a phone number and if it is valid, insert it into the db
void database::addRecord(unsigned long number, unsigned short minutes) {
	phoneNumber phone{number};
	if (phone.isValid()) {
		callRecords.insert({phone, minutes});
	}
}

// prints out the top N phone numbers and number of minutes sorted by
// number of minutes
void database::printTopBusy(unsigned int N) const {
	// go through all of the entries in the db and group by phone number
	// and total the minutes
	map<phoneNumber, unsigned int> totalMinutes;
	for(auto& elem : callRecords) {
		auto found = totalMinutes.find(elem.first);
		if (found != totalMinutes.end()) {
			// if the phone number was found already, just add in the additional minutes
			found->second += elem.second;
		} else {
			// otherwise, add a new entry for the phone number
			totalMinutes.insert({elem.first, elem.second});
		}
	}

	// I am not taking into account ties here for the same number
	// of minutes. If you wanted to do that, you could use a set
	// for the second argument and then keep a list of ties per
	// minute total
	// This is just flipping the order of the minutes and phone numbers
	// while also keeping it sorted by minutes.
	multimap<unsigned int, phoneNumber> sortedMinutes;
	for(auto& elem : totalMinutes) {
		sortedMinutes.insert({elem.second, elem.first});
	}

	// Since the multimap is sorted by phone number decending, we just start
	// at the end and print the N elements from the end.
	auto iter = sortedMinutes.rbegin();
	unsigned int count = 0;
	while (count++ < N && iter != sortedMinutes.rend()) {
		cout << iter->second.number() << '\t' << iter->first << endl;
		++iter;
	}
}
