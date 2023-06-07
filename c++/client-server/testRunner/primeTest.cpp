//
//  primeTest.cpp
//  testRunner
//
//  Created by Scott Gustafson on 7/1/16.
//  Copyright © 2016 Garlic Software LLC. All rights reserved.
//

#include "prime.h"
#include <limits.h>
#include "gtest/gtest.h"

// test the different strategies just to make sure they are all returning the same results
class PrimeTableStrategyTest : public ::testing::TestWithParam<prime::strategy> {
};

TEST_P(PrimeTableStrategyTest, TestRangeOfTable) {
	EXPECT_FALSE(prime::is_prime(0, GetParam()));
	EXPECT_FALSE(prime::is_prime(1, GetParam()));
	EXPECT_TRUE(prime::is_prime(2, GetParam()));	// first prime
	EXPECT_TRUE(prime::is_prime(3, GetParam()));
	EXPECT_FALSE(prime::is_prime(4, GetParam()));
	EXPECT_TRUE(prime::is_prime(5, GetParam()));
	EXPECT_FALSE(prime::is_prime(6, GetParam()));
	EXPECT_TRUE(prime::is_prime(23, GetParam()));
	EXPECT_FALSE(prime::is_prime(65520, GetParam()));
	EXPECT_TRUE(prime::is_prime(65521, GetParam()));
	EXPECT_FALSE(prime::is_prime(65522, GetParam()));
	EXPECT_TRUE(prime::is_prime(65537, GetParam()));
	EXPECT_FALSE(prime::is_prime(104728, GetParam()));
	EXPECT_TRUE(prime::is_prime(104729, GetParam()));	// last table prime (10,000th)
	EXPECT_FALSE(prime::is_prime(104730, GetParam()));
	EXPECT_TRUE(prime::is_prime(104743, GetParam()));
}

INSTANTIATE_TEST_CASE_P(StrategyTest, PrimeTableStrategyTest,
		::testing::Values(prime::strategyDefault, prime::strategyLinear, prime::strategyBinary, prime::strategySieve));

// Performance Tests
class PerformanceTest : public ::testing::TestWithParam<prime::strategy> {
};

TEST_P(PerformanceTest, MidTableLoop100) {
	for (unsigned char x = 0; x < 100; ++x) {
		EXPECT_FALSE(prime::is_prime(65520, GetParam()));
		EXPECT_TRUE(prime::is_prime(65521, GetParam()));
		EXPECT_FALSE(prime::is_prime(65522, GetParam()));
		EXPECT_TRUE(prime::is_prime(65537, GetParam()));
	}
}

TEST_P(PerformanceTest, SmallPrimeLoop100) {
	for (unsigned char x = 0; x < 100; ++x) {
		EXPECT_TRUE(prime::is_prime(2, GetParam()));
		EXPECT_TRUE(prime::is_prime(3, GetParam()));
		EXPECT_FALSE(prime::is_prime(4, GetParam()));
		EXPECT_TRUE(prime::is_prime(5, GetParam()));
	}
}

TEST_P(PerformanceTest, LargePrimeLoop100) {
	for (unsigned char x = 0; x < 100; ++x) {
		EXPECT_FALSE(prime::is_prime(104728, GetParam()));
		EXPECT_TRUE(prime::is_prime(104729, GetParam()));
	}
}

INSTANTIATE_TEST_CASE_P(TimingTest, PerformanceTest,
		::testing::Values(prime::strategyLinear, prime::strategyBinary, prime::strategySieve));

// standards compliance on a 64bit system is that int is 4 bytes (32 bits).
// the next two tests test the maximums and run kind of long
// ~150 and ~309 seconds respectively on some old hardware

// INT_MAX == 0x7FFFFFFF == 2147483647
TEST(is_primeTest, Test_INT_MAX) {
	EXPECT_TRUE(prime::is_prime(INT_MAX));
}

// UINT_MAX == 0xFFFFFFFF == 4294967295
TEST(is_primeTest, Test_UINT_MAX) {
	EXPECT_FALSE(prime::is_prime(UINT_MAX));
}
