/*
 * phoneNumber_test.cpp
 *
 *  Created on: Jun 13, 2018
 *      Author: scott
 */

#include "phoneNumber.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>

class phoneNumber_test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( phoneNumber_test );
	CPPUNIT_TEST( testConstructors );
	CPPUNIT_TEST( testSettersAndGetters );
	CPPUNIT_TEST( testIsValid );
	CPPUNIT_TEST_SUITE_END();

protected:
	void testConstructors();
	void testSettersAndGetters();
	void testIsValid();
};

CPPUNIT_TEST_SUITE_REGISTRATION( phoneNumber_test );

void phoneNumber_test::testConstructors() {
	phoneNumber *test = nullptr;
	CPPUNIT_ASSERT_NO_THROW(test = new phoneNumber{0UL});
	CPPUNIT_ASSERT_EQUAL(0UL, test->number());
	delete test;

	phoneNumber test2{12323UL};
	CPPUNIT_ASSERT_EQUAL(12323UL, test2.number());

}


void phoneNumber_test::testSettersAndGetters() {
	phoneNumber test{0UL};

	CPPUNIT_ASSERT_NO_THROW(test.setNumber(0UL));
	CPPUNIT_ASSERT_NO_THROW(test.number());
	CPPUNIT_ASSERT_EQUAL(0UL, test.number());

	CPPUNIT_ASSERT_NO_THROW(test.setNumber(-1UL));
	CPPUNIT_ASSERT_EQUAL(-1UL, test.number());

	CPPUNIT_ASSERT_NO_THROW(test.setNumber(17205551212UL));
	CPPUNIT_ASSERT_EQUAL(17205551212UL, test.number());

	CPPUNIT_ASSERT_NO_THROW(test.setNumber("17205551213"));
	CPPUNIT_ASSERT_EQUAL(17205551213UL, test.number());

	CPPUNIT_ASSERT_NO_THROW(test.setNumber(""));
	CPPUNIT_ASSERT_EQUAL(0UL, test.number());

	CPPUNIT_ASSERT_NO_THROW(test.setNumber("0"));
	CPPUNIT_ASSERT_EQUAL(0UL, test.number());

	CPPUNIT_ASSERT_THROW(test.setNumber(" "), std::out_of_range);
	CPPUNIT_ASSERT_EQUAL(0UL, test.number());

	CPPUNIT_ASSERT_THROW(test.setNumber("(720) 555-1212"), std::out_of_range);
	CPPUNIT_ASSERT_EQUAL(0UL, test.number());

	CPPUNIT_ASSERT_THROW(test.setNumber("+1-720-555-1212"), std::out_of_range);
	CPPUNIT_ASSERT_EQUAL(0UL, test.number());

	CPPUNIT_ASSERT_THROW(test.setNumber("ext. 1234"), std::out_of_range);
	CPPUNIT_ASSERT_EQUAL(0UL, test.number());

	CPPUNIT_ASSERT_THROW(test.setNumber("555-1212"), std::out_of_range);
	CPPUNIT_ASSERT_EQUAL(0UL, test.number());
}

void phoneNumber_test::testIsValid() {
	phoneNumber test{0UL};
	CPPUNIT_ASSERT_NO_THROW(test.isValid());
	CPPUNIT_ASSERT(false == test.isValid());

	test.setNumber(1234);
	CPPUNIT_ASSERT_NO_THROW(test.isValid());
	CPPUNIT_ASSERT(true == test.isValid());

	test.setNumber(17205551212);
	CPPUNIT_ASSERT_NO_THROW(test.isValid());
	CPPUNIT_ASSERT(true == test.isValid());

	test.setNumber(19999999999);
	CPPUNIT_ASSERT_NO_THROW(test.isValid());
	CPPUNIT_ASSERT(true == test.isValid());

	test.setNumber(20000000000);
	CPPUNIT_ASSERT_NO_THROW(test.isValid());
	CPPUNIT_ASSERT(false == test.isValid());
}
