// Copyright © 2020 R. Scott Gustafson. All rights reserved.

#include "csv.h"

#include <fstream>
#include <iostream>


csv::csv(void) {
    // load in the default data
    const static std::string fileName{"../code_problem_data.csv"};

    std::ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        std::cerr << "failed to open " << fileName << '\n';
        return;
    }

    std::string line;
    while (std::getline(file, line, '\n') ) {
        format data = split(line);
        m_data.push_back(data);
    }
}

csv::format csv::split(std::string line) {
    csv::format result{0.0, 0.0, 0.0, 0.0};

    result.time = stod(line);
    line.erase(0, line.find(',') + 1);
    result.lat = stod(line);
    line.erase(0, line.find(',') + 1);
    result.lon = stod(line);
    line.erase(0, line.find(',') + 1);
    result.alt = stod(line);

    return result;
}

#if defined(TESTING)
#include "gtest/gtest.h"

TEST(csv, csv) {
    csv file;
    ASSERT_EQ(file.m_data.size(), 501);

    auto iter = file.m_data.begin() + 99; // line 100

    ASSERT_DOUBLE_EQ ((*iter).time,  1532333354.04);
    ASSERT_DOUBLE_EQ ((*iter).lat,  34.7056);
    ASSERT_DOUBLE_EQ ((*iter).lon,  128.26326);
    ASSERT_DOUBLE_EQ ((*iter).alt,  1654.3275);
}

TEST(csv, split) {
    std::string line{"1532332954.04,39.19704,127.65702,381.22697"};
    csv file;
    csv::format data = file.split(line);
    ASSERT_DOUBLE_EQ (data.time,  1532332954.04);
    ASSERT_DOUBLE_EQ (data.lat,  39.19704);
    ASSERT_DOUBLE_EQ (data.lon,  127.65702);
    ASSERT_DOUBLE_EQ (data.alt,  381.22697);
}

#endif // TESTING