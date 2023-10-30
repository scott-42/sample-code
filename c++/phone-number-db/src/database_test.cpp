/*
 * database_test.cpp
 *
 *  Created on: Jun 13, 2018
 *      Author: scott
 * Copyright © 2018 R. Scott Gustafson. All rights reserved.
 */

#include "database.h"
#include <random>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>

class database_test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( database_test );
	CPPUNIT_TEST( testAddRecord );
	CPPUNIT_TEST_SUITE_END();

protected:
	void testAddRecord();
};

CPPUNIT_TEST_SUITE_REGISTRATION( database_test );

void database_test::testAddRecord() {
	database db;

	CPPUNIT_ASSERT( true == db.callRecords.empty());
	db.addRecord(12345, 42);
	CPPUNIT_ASSERT( false == db.callRecords.empty());
	CPPUNIT_ASSERT(1 == db.callRecords.size());
	CPPUNIT_ASSERT(12345 == (*db.callRecords.begin()).first.number());
	CPPUNIT_ASSERT(42 == (*db.callRecords.begin()).second);

	// make sure an invalid number is not added
	db.addRecord(0, 34);
	CPPUNIT_ASSERT(1 == db.callRecords.size());


	using phone_distribution = normal_distribution<>;
	using minute_distribution = uniform_int_distribution<>;

	// note, not using a random_device here so we get the generic rand which
	// always has the same seed for testing
	mt19937 gen{};
	phone_distribution exchange {1000.0, 500.0};
	minute_distribution small {1, 60};
	auto extension = bind(exchange, gen);
	auto phone = bind([&extension](unsigned long ext) -> unsigned long {return extension() + ext;}, 17205550000UL);
	auto minutes = bind(small, gen);

	for (int x = 0; x < 10000; ++x) {
		db.addRecord(phone(), minutes());
	}

	CPPUNIT_ASSERT(10001 == db.callRecords.size());
}
