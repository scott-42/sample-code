## Problem Statement

One state machine prints the wall clock time to stdout every 1.4 seconds in HH:MM:SS.mm format,
where HH = hours since start of day (0-23), MM = minute in current hour (0-59), SS = seconds in 
current minute (0-59), and mm = milliseconds in current second (00-99).

The other state machine prints the points around the circumference of a unit circle 
(radius = 1) to stderr every 1.2 seconds.  The starting angle = zero and the angle is 
incremented each time it is printed according to the following schedule: 1 degree, 4 
degrees, 13 degrees, 7 degrees, 20 degrees (after incrementing by 20, wrap around and 
start again at 1.)  The output should be formatted as: "x, y, <time>", where <time> 
can have any format provided that it has at least millisecond resolution.  The x and 
y coordinates can be any format you choose.

## Building
### Dev Container Version
If you have Microsoft Visual Code and Docker then the DevContainer version is fully self-contained and the build is very simple. Just open a terminal in Code and use the command line build below.
### Command Line
```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./sample
1.00000, 0.00000, 19:12:50.70
19:12:50.90
0.99985, 0.01745, 19:12:51.90
19:12:52.30
0.99619, 0.08716, 19:12:53.10
19:12:53.70
0.95106, 0.30902, 19:12:54.30
19:12:55.10
0.90631, 0.42262, 19:12:55.50
19:12:56.50
0.70711, 0.70711, 19:12:56.70
19:12:57.90
0.69466, 0.71934, 19:12:57.90
0.64279, 0.76604, 19:12:59.10
19:12:59.30
0.45399, 0.89101, 19:13:00.30
19:13:00.70
0.34202, 0.93969, 19:13:01.50
19:13:02.10
0.00000, 1.00000, 19:13:02.70
19:13:03.50
-0.01745, 0.99985, 19:13:03.90
19:13:04.90
-0.08716, 0.99619, 19:13:05.10
19:13:06.30
-0.30902, 0.95106, 19:13:06.30
-0.42262, 0.90631, 19:13:07.50
19:13:07.70
```

## Notes
Compiled and run under Ubuntu 22.04 with gcc
```
$ gcc --version
gcc (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0
```
