/*
 * sample.cpp
 *
 *  Created on: Jun 13, 2018
 *      Author: scott
 */

#include <iostream>
#include <random>
#include <functional>
#include "database.h"

#if defined(TEST)

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

#endif

using namespace std;

database db;

//Function-1: add a record for a single call. Takes 2 parameters: calling number and number of minutes.
void addRecord(unsigned long number, unsigned short minutes) {
	db.addRecord(number, minutes);
}

//Function-2: print most busy numbers. Takes single parameter (N) and prints N number of telephone
//numbers along with their total minutes in sorted order.
// Assuming a descending order from highest number of minutes to lowest.
void printTopBusy(unsigned int N) {
	cout << "number" << "\t\t" << "minutes" << endl;
	db.printTopBusy(N);
}

void addSampleData(void);

int main(int argc, const char * argv[]) {
#if defined(TEST)
	// Create the event manager and test controller
	CPPUNIT_NS::TestResult controller;

	// Add a listener that collects test result
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener( &result );

	// Add a listener that print dots as test run.
	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener( &progress );

	// Add the top suite to the test runner
	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller );
#endif

	addSampleData();
	unsigned int numberToPrint = 10; // defaulting to 10
	if (argc == 2) {
		numberToPrint = atoi(argv[1]);
	}
	printTopBusy(numberToPrint);

#if defined(TEST)
	// Print test in a compiler compatible format.
	CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
	outputter.write();

	return result.wasSuccessful() ? 0 : 1;
#else
	return 0;
#endif
}

// This function adds 10000 records to the database.
void addSampleData(void) {
	random_device rd;

	// I'm using a normal distribution (aka bell curve) for the phone numbers so I can
	// count on having many duplicates within the numbers when I go to add them together.
	using phone_distribution = normal_distribution<>;
	using minute_distribution = uniform_int_distribution<>;

	mt19937 gen{rd()};
	phone_distribution exchange {1000.0, 500.0};
	minute_distribution small {1, 60};
	auto extension = bind(exchange, gen);
	auto phone = bind([&extension](unsigned long ext) -> unsigned long {return extension() + ext;}, 17205550000UL);
	auto minutes = bind(small, gen);

	for (int x = 0; x < 10000; ++x) {
		addRecord(phone(), minutes());
	}
}
