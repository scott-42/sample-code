# cpp-sample
C++ Sample Code

## Problem Statement
Design a client/server application using recent C++ (11 and +) testing the primality of an unsigned integer. The client is expected to issue a request to the server, which will return a boolean value. Ensure that you can have concurrent calculations occurring at any moment. Bonus points for speed optimization, and support of large, if not *very* large number. Design the code to run within a test framework of your choosing. Indicate how you would cover your code, or optionally, write unit tests to illustrate code coverage.

## Usage
The tcp port default is set to 22000.

### Server
`$ ./server`

### Client
`$ ./client <hostname> <number to test>`

Example: `./client localhost 104729`

### testRunner
`$ ./testRunner`

The server is currently using two threads and can handle two clients simutaneously. You can manually test this by calling client with a long running test number and then calling with a smaller number in another thread. For example:
Example: In terminal one run: `./client localhost 184467449` and in terminal two run: `./client localhost 65521`

## Notes
Compiled and run using Xcode 7.3.1 on a Mac.

This is using the following submodules:
- boost::asio 1.10.6 http://think-async.com/Asio/
- boost::math 1.61.0 http://www.boost.org/users/history/version_1_61_0.html
- boost::coroutine and dependencies
  - boost::thread
  - boost::system
  - boost::context
- googletest latest 

Basic Info on Primality Test [Wikipedia](https://en.wikipedia.org/wiki/Primality_test)

This code is only designed to work with at most 32 bit integers as these algorithms are too slow for 64 bit values or larger. There are other algorithms for very large prime tests used primarily in crypto which could be adapted to fit this if the need existed. There are also faster sieve algorithms (Sieve of Eratosthenes) as can be found in YAFU https://sites.google.com/site/bbuhrow/.

# Testing Output
```
Running main() from main.cpp
[==========] Running 15 tests from 3 test cases.
[----------] Global test environment set-up.
[----------] 2 tests from is_primeTest
[ RUN      ] is_primeTest.Test_INT_MAX
[       OK ] is_primeTest.Test_INT_MAX (150445 ms)
[ RUN      ] is_primeTest.Test_UINT_MAX
[       OK ] is_primeTest.Test_UINT_MAX (312641 ms)
[----------] 2 tests from is_primeTest (463086 ms total)

[----------] 4 tests from StrategyTest/PrimeTableStrategyTest
[ RUN      ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/0
[       OK ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/0 (6 ms)
[ RUN      ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/1
[       OK ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/1 (11 ms)
[ RUN      ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/2
[       OK ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/2 (6 ms)
[ RUN      ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/3
[       OK ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/3 (21 ms)
[----------] 4 tests from StrategyTest/PrimeTableStrategyTest (44 ms total)

[----------] 9 tests from TimingTest/PerformanceTest
[ RUN      ] TimingTest/PerformanceTest.MidTableLoop100/0
[       OK ] TimingTest/PerformanceTest.MidTableLoop100/0 (22 ms)
[ RUN      ] TimingTest/PerformanceTest.MidTableLoop100/1
[       OK ] TimingTest/PerformanceTest.MidTableLoop100/1 (0 ms)
[ RUN      ] TimingTest/PerformanceTest.MidTableLoop100/2
[       OK ] TimingTest/PerformanceTest.MidTableLoop100/2 (796 ms)
[ RUN      ] TimingTest/PerformanceTest.SmallPrimeLoop100/0
[       OK ] TimingTest/PerformanceTest.SmallPrimeLoop100/0 (0 ms)
[ RUN      ] TimingTest/PerformanceTest.SmallPrimeLoop100/1
[       OK ] TimingTest/PerformanceTest.SmallPrimeLoop100/1 (0 ms)
[ RUN      ] TimingTest/PerformanceTest.SmallPrimeLoop100/2
[       OK ] TimingTest/PerformanceTest.SmallPrimeLoop100/2 (1 ms)
[ RUN      ] TimingTest/PerformanceTest.LargePrimeLoop100/0
[       OK ] TimingTest/PerformanceTest.LargePrimeLoop100/0 (16 ms)
[ RUN      ] TimingTest/PerformanceTest.LargePrimeLoop100/1
[       OK ] TimingTest/PerformanceTest.LargePrimeLoop100/1 (0 ms)
[ RUN      ] TimingTest/PerformanceTest.LargePrimeLoop100/2
[       OK ] TimingTest/PerformanceTest.LargePrimeLoop100/2 (639 ms)
[----------] 9 tests from TimingTest/PerformanceTest (1474 ms total)

[----------] Global test environment tear-down
[==========] 15 tests from 3 test cases ran. (464604 ms total)
[  PASSED  ] 15 tests.
Program ended with exit code: 0
```