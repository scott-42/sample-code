# LLA-to-ECEF Coding Challenge

## Problem Statement
In the field of remote sensing, a common task that comes up is coordinate conversion.
Two common coordinate systems are geodetic coordinates, consisting of latitude,
longitude, and altitude (LLA) and geocentric coordinates, also called Earth-centered,
Earth-fixed (ECEF). Descriptions of these coordinate systems as well as the
transformations between them are described in 
[Datum Transformations of GPS Positions.PDF](https://microem.ru/files/2012/08/GPS.G1-X-00006.pdf) 
Application Note, July 5, 1999, μ-blox ag (http://www.u-blox.ch) {The PDF is attached to this repo for convenience}.

In the package accompanying this document, the file `code_problem_data.csv`
contains data representing a time series of an object using LLA coordinates. It is your
task to write a program that returns the ECEF velocity vector of the object at any
requested time.

### Expected Subtasks
- Read the CSV file
- Convert LLA to ECEF
- Calculate ECEF velocity at the time points given in the input file
- Interpolate ECEF velocity for any requested time

### Calculating ECEF Velocity
The expected baseline for calculating ECEF velocities is the discrete ∆Position/∆Time
between consecutive points. The velocity at the first input point is defined as 0. Velocity
at times that don’t coincide with points in the input file should be calculated by linearly
interpolating the velocities calculated for input points. If you are using a more complex
method for calculating or interpolating velocity, please note how and why you are
doing it in your readme (it is not expected that you differ from the baseline).

## Input
The input CSV file located in the package accompanying this document should be read
in by your program. The CSV file consists of rows of comma-separated values, where
each row contains the following fields:
- Time since the Unix epoch [seconds]
- WGS84 Latitude [degrees]
- WGS84 Longitude [degrees]
- WGS84 Altitude [kilometers]
### Sample Data Extract Example
```
1532333099.04,37.50902,127.8791,904.34352
1532333104.04,37.45203,127.88671,921.13217
1532333109.04,37.39512,127.89432,937.8375
1532333114.04,37.33829,127.90192,954.4595
1532333119.04,37.28154,127.90952,970.99819
1532333124.04,37.22487,127.91712,987.45354
```

## Output
Your program should call the function or class you created, and evaluate the ECEF
velocity vector at two specific times: `1532334000` and `1532335268` (both given as
seconds since the Unix epoch). The result should be printed to stdout for both of the
given times.

## Allowed Resources
Your program should be written in C++ (C++11 or C++14).You are encouraged to use
online resources when completing the challenge; however you may not directly copy
non-trivial pieces of code or solutions. Code may use the C++ Standard Library. C++
code is expected to be built and run in a Linux environment.

---

# Solution

To build on a linux machine with cmake, make, and gcc you should only need to
run cmake which will generate the Makefile, then run make. Included is a DevContainer
(MS Visual Code with Docker) with all of the requirements preinstalled.

```
% mkdir build
% cd build
% cmake ..
% make
```

This will create two binaries, one regular and one for testing. Testing is done with 
googetest framework and is not extensive. Some rudimentary tests were included to 
show capability, not to exhaustively test the code.

```
% ./sample-test
Running main() from /googletest/googletest/src/gtest_main.cc
[==========] Running 7 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from csv
[ RUN      ] csv.csv
[       OK ] csv.csv (0 ms)
[ RUN      ] csv.split
[       OK ] csv.split (0 ms)
[----------] 2 tests from csv (0 ms total)

[----------] 1 test from coord
[ RUN      ] coord.coord
[       OK ] coord.coord (0 ms)
[----------] 1 test from coord (0 ms total)

[----------] 2 tests from coordECEF
[ RUN      ] coordECEF.coordECEF
[       OK ] coordECEF.coordECEF (0 ms)
[ RUN      ] coordECEF.distanceTo
[       OK ] coordECEF.distanceTo (0 ms)
[----------] 2 tests from coordECEF (0 ms total)

[----------] 2 tests from coordLLA
[ RUN      ] coordLLA.coordLLA
[       OK ] coordLLA.coordLLA (0 ms)
[ RUN      ] coordLLA.ecef
[       OK ] coordLLA.ecef (0 ms)
[----------] 2 tests from coordLLA (0 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 4 test suites ran. (1 ms total)
[  PASSED  ] 7 tests.```

```
% ./sample
```
Time: 1532334000 Velocity: 1389.526667224982
Time: 1532335268 Velocity: 3891.3052647121899
```