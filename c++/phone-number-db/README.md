## Problem Statement
We want to report top-N busy users (phone number) in total minutes they talked.
 
Write two functions along a small test app (main) using those functions.

Function-1: add a record for a single call. Takes 2 parameters: calling number and number of minutes.

Function-2: print most busy numbers. Takes single parameter (N) and prints N number of telephone numbers along with their total minutes in sorted order.
 
This application must be compliable in gcc 4.1 or above and runnable.

Use std library containers, one or more is OK.
## Solution
Function-1 see `database::addRecord(unsigned long number, unsigned short minutes)`

Function-2 see `database::printTopBusy(unsigned int N)`
## Building
```
$ make clean
$ make
$ sample 5
number		minutes
17205550749	578
17205550638	554
17205551106	546
17205550686	546
17205551004	508
```
The program takes one argument as a number and prints out the number of entries. There is no real formatting of the output as it just uses a tab to delimit the text. If you don't provide a number it uses the default of 10.

## Testing
If you have cppunit installed,
```
$ apt search libcppunit
Sorting... Done
Full Text Search... Done
libcppunit-1.13-0v5/xenial,now 1.13.2-2.1 amd64 [installed]
  Unit Testing Library for C++

libcppunit-dev/xenial,now 1.13.2-2.1 amd64 [installed]
  Unit Testing Library for C++

libcppunit-doc/xenial,xenial,now 1.13.2-2.1 all [installed]
  Unit Testing Library for C++
```
then you can run the test suite by
```
$ make clean
$ make test
$ sample-test 5
phoneNumber_test::testConstructors : OK
phoneNumber_test::testSettersAndGetters : OK
phoneNumber_test::testIsValid : OK
database_test::testAddRecord : OK
number		minutes
17205551021	594
17205550893	562
17205550988	539
17205551122	519
17205550944	503
OK (4)
```
## Notes
Compiled and run under Ubuntu 16.04 with gcc and cppunit
```
$ gcc --version
gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609
```
