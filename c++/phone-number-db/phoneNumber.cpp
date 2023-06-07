/*
 * phoneNumber.cpp
 *
 *  Created on: Jun 13, 2018
 *      Author: scott
 */

#include "phoneNumber.h"

#include <cctype>
#include <stdexcept>

using namespace std;

phoneNumber::phoneNumber(unsigned long value = 0)
		: m_number{value} {

}

phoneNumber::~phoneNumber(void) {

}

// a valid phone number in this system is between 1 and 10 digits.
// This is not a real phone number validity check as I'm only looking at
// country code 1 at the high end and all possible number for area codes
// and numbers in those areas. This also leaves open any smaller numbers
// like extension numbers and any custom numbers.
bool phoneNumber::isValid(void) const noexcept {
	if (m_number == 0)
		return false;
	// +1 NPA Nxx xxxx
	if (m_number > 19999999999)
		return false;
	return true;
}

void phoneNumber::setNumber(unsigned long phone) noexcept {
	m_number = phone;
}

// the phone string is assumed to only contain digits
void phoneNumber::setNumber(const std::string& phone) {
	unsigned long value = 0;
	for (auto& digit : phone) {
		if (!isdigit(digit)) {
			m_number = 0; // invalidate the number if we are about to throw and error
			throw out_of_range("The phone number can only contain digits.");
		}
		value = value * 10 + (digit - '0');
	}
	setNumber(value);
}

unsigned long phoneNumber::number(void) const noexcept {
	return m_number;
}


bool phoneNumber::operator<(const phoneNumber& rhs) const {
	return m_number < rhs.m_number;
}
