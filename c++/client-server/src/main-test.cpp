//
//  main.cpp
//  testRunner
//
//  Created by Scott Gustafson on 7/1/16.
//  Copyright © 2016 Garlic Software LLC. All rights reserved.
//

#include <iostream>
#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
	std::cout << "Running main() from main.cpp" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
