//
//  prime.cpp
//  server
//
//  Created by Scott Gustafson on 7/1/16.
//  Copyright © 2016 Garlic Software LLC. All rights reserved.
//

#include "prime.h"
#include <cmath>
#include <vector>
#include "special_functions_prime.h"

namespace prime {

const bool linear_search(const unsigned int value);
const bool binary_search(const unsigned int value);
const bool sieve(const unsigned int value);

const bool is_prime(const unsigned int value, const strategy strat) {
	// simple cases as primes must be greater than 1
	if (value == 0 || value == 1) {
		return false;
	}
	
	if (value <= boost::math::prime(9999)) {
		if (strat == strategyDefault || strat == strategyBinary) {
			return binary_search(value);
		} else if (strat == strategyLinear) {
			return linear_search(value);
		} else {
			// do nothing and run the sieve below
		}
	}

	return sieve(value);
}

// simple linear search, plenty fast (less than 1 ms)
// O(n)
const bool linear_search(const unsigned int value) {
	for (unsigned short x = 0; (x < 10000); ++x) {
		unsigned int test_prime = boost::math::prime(x);
		if (test_prime == value) {
			return true;
		} else if (test_prime > value) {
			return false;
		}
	}
	return false;
}

// simple binary search for the number should be quick enough
// O(log n)
const bool binary_search(const unsigned int value) {
	unsigned short min = 0, max = 9999, mid = max / 2;
	while (true) {
		unsigned int test_prime = boost::math::prime(mid);
		
		if (test_prime == value) {
			return true;
		} else if (test_prime < value) {
			if (min == mid) {
				return false;
			}
			min = mid;
		} else {
			if (max == mid) {
				return false;
			}
			max = mid;
		}
		if (min == max) {
			return false;
		}
		mid = ((max - min) / 2) + min;
		if ((min != 0) && ((max - min) == 1) && (min == mid)) {
			mid++;
		}
		if (mid < min || mid > max) {
			return false;
		}
	}
	return false;
}

// This implements a crude Sieve of Atkin to find prime numbers
// see https://en.wikipedia.org/wiki/Sieve_of_Atkin
// I borrowed this crude code from the web and it should not be used for
// any kind of production as is good enough only for sample code to test
// against.
const bool sieve(const unsigned int value) {
	std::vector<bool> test((long)value + 1, false);
	
	//defines square root of m
	unsigned long root = ceil(sqrt(value));
	
	//sieve axioms
	for(unsigned long x = 1; x <= root; x++) {
		for(unsigned long y = 1; y <= root; y++) {
			unsigned long i = (4 * x * x) + (y * y);
			if (i <= value && (i % 12 == 1 || i % 12 == 5)) {
				test[i] = !test[i];
			}
			i = (3 * x * x) + (y * y);
			if (i <= value && i % 12 == 7) {
				test[i] = !test[i];
			}
			i = (3 * x * x) - (y * y);
			if (x > y && i <= value && i % 12 == 11) {
				test[i] = !test[i];
			}
		}
	}
	
	//marks 2,3,5 and 7 as prime numbers
	test[2]=test[3]=test[5]=test[7]=true;
	
	//marks all multiples of primes as non primes
	for(unsigned long r = 5; r <= root; r++) {
		if(test[r]) {
			for(unsigned long j = r * r; j <= value; j += r * r) {
				test[j] = false;
			}
		}
	}
	
	return test[value];
}

} // namespace prime


