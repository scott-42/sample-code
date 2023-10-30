/*
 * phoneNumber.h
 *
 *  Created on: Jun 13, 2018
 *      Author: scott
 * Copyright © 2018 R. Scott Gustafson. All rights reserved.
*/

#ifndef PHONENUMBER_H_
#define PHONENUMBER_H_

#include <string>

class phoneNumber {
private:
	unsigned long m_number;
public:
	phoneNumber(unsigned long value);
	virtual ~phoneNumber(void);

	bool isValid(void) const noexcept;

	void setNumber(unsigned long phone) noexcept;
	void setNumber(const std::string& phone);
	unsigned long number(void) const noexcept;

	bool operator<(const phoneNumber& rhs) const;
};

#endif /* PHONENUMBER_H_ */
