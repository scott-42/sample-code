# Problem Statement
Design a client/server application using recent C++ (11 and +) testing the primality of an unsigned integer. The client is expected to issue a request to the server, which will return a boolean value. Ensure that you can have concurrent calculations occurring at any moment. Bonus points for speed optimization, and support of large, if not *very* large number. Design the code to run within a test framework of your choosing. Indicate how you would cover your code, or optionally, write unit tests to illustrate code coverage.

# Solution

## Usage
The tcp port default is set to 22000.

### Server
Start the server in one terminal window
```
./sample-server
```

### Client
In another terminal window try the client. `sample-client <hostname> <number to test>`
```
./sample-client localhost 104729
```

### Multi-thread
The server is currently using two threads and can handle two clients simultaneously. You can manually test this by calling client with a long running test number and then calling with a smaller number in another thread. For example:
In terminal one run: 
```
./sample-client localhost 184467449
``` 
and in terminal two run: 
```
./sample-client localhost 65521
```

# Notes
Reworked to use Dev Containers (aka MS Visual Code and Docker).

Depends on [boost](https://github.com/boostorg/boost) and [googletest](https://github.com/google/googletest) from Github. These are auto included and built for the docker image.

Basic Info on Primality Test [Wikipedia](https://en.wikipedia.org/wiki/Primality_test)

This code is only designed to work with at most 32 bit integers as these algorithms are too slow for 64 bit values or larger. There are other algorithms for very large prime tests used primarily in crypto which could be adapted to fit this if the need existed. There are also faster sieve algorithms (Sieve of Eratosthenes) as can be found in YAFU https://sites.google.com/site/bbuhrow/.

# Testing Output
```
$ ./sample-test
Running main() from /googletest/googletest/src/gtest_main.cc
[==========] Running 15 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from is_primeTest
[ RUN      ] is_primeTest.Test_INT_MAX
[       OK ] is_primeTest.Test_INT_MAX (104276 ms)
[ RUN      ] is_primeTest.Test_UINT_MAX
[       OK ] is_primeTest.Test_UINT_MAX (248310 ms)
[----------] 2 tests from is_primeTest (352586 ms total)

[----------] 4 tests from StrategyTest/PrimeTableStrategyTest
[ RUN      ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/0
[       OK ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/0 (4 ms)
[ RUN      ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/1
[       OK ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/1 (4 ms)
[ RUN      ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/2
[       OK ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/2 (4 ms)
[ RUN      ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/3
[       OK ] StrategyTest/PrimeTableStrategyTest.TestRangeOfTable/3 (13 ms)
[----------] 4 tests from StrategyTest/PrimeTableStrategyTest (26 ms total)

[----------] 9 tests from TimingTest/PerformanceTest
[ RUN      ] TimingTest/PerformanceTest.MidTableLoop100/0
[       OK ] TimingTest/PerformanceTest.MidTableLoop100/0 (6 ms)
[ RUN      ] TimingTest/PerformanceTest.MidTableLoop100/1
[       OK ] TimingTest/PerformanceTest.MidTableLoop100/1 (0 ms)
[ RUN      ] TimingTest/PerformanceTest.MidTableLoop100/2
[       OK ] TimingTest/PerformanceTest.MidTableLoop100/2 (547 ms)
[ RUN      ] TimingTest/PerformanceTest.SmallPrimeLoop100/0
[       OK ] TimingTest/PerformanceTest.SmallPrimeLoop100/0 (0 ms)
[ RUN      ] TimingTest/PerformanceTest.SmallPrimeLoop100/1
[       OK ] TimingTest/PerformanceTest.SmallPrimeLoop100/1 (0 ms)
[ RUN      ] TimingTest/PerformanceTest.SmallPrimeLoop100/2
[       OK ] TimingTest/PerformanceTest.SmallPrimeLoop100/2 (0 ms)
[ RUN      ] TimingTest/PerformanceTest.LargePrimeLoop100/0
[       OK ] TimingTest/PerformanceTest.LargePrimeLoop100/0 (4 ms)
[ RUN      ] TimingTest/PerformanceTest.LargePrimeLoop100/1
[       OK ] TimingTest/PerformanceTest.LargePrimeLoop100/1 (0 ms)
[ RUN      ] TimingTest/PerformanceTest.LargePrimeLoop100/2
[       OK ] TimingTest/PerformanceTest.LargePrimeLoop100/2 (436 ms)
[----------] 9 tests from TimingTest/PerformanceTest (996 ms total)

[----------] Global test environment tear-down
[==========] 15 tests from 3 test suites ran. (353609 ms total)
[  PASSED  ] 15 tests.
```