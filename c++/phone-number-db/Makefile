#
# Makefile
#
#  Created on: Jun 13, 2018
#      Author: scott
#

CXXFLAGS =	-std=c++14 -O2 -g -Wall -fmessage-length=0

OBJS =		sample.o phoneNumber.o database.o
TEST_OBJS =	phoneNumber_test.o database_test.o

LIBS =		
TEST_LIBS =	-l cppunit

TARGET =	sample
TEST_TARGET = sample-test

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

$(TEST_TARGET):	$(OBJS) $(TEST_OBJS)
	$(CXX) -D TEST -o $(TEST_TARGET) $(OBJS) $(TEST_OBJS) $(LIBS) $(TEST_LIBS)

all:	$(TARGET)

test:	CXXFLAGS += -DTEST
test:	$(TEST_TARGET)

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

phoneNumber.o: phoneNumber.cpp phoneNumber.h
phoneNumber_test.o: phoneNumber_test.cpp phoneNumber.o
database.o: database.cpp database.h
database_test.o: database_test.cpp database.o
sample.o: sample.cpp database.h
