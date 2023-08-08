// Copyright © 2020 R. Scott Gustafson. All rights reserved.

#include "coord.h"
#include <cmath>

coordECEF coordLLA::ecef(void) {
    // WGS84 Parameters
    const double a = 6378137.0;
    const double f = 1.0 / 298.257223563;
    const double b = a * (1.0 - f); // 6356752.31424518
    const double e2 = 1.0 - std::pow(b, 2) / std::pow(a, 2); // e squared (not Euler's)
    const double pi = std::acos(-1);
    const double phi = latitude() * pi / 180; // convert to radians
    const double lambda = longitude() * pi / 180; // convert to radians
    const double N = a / std::sqrt(1.0 - e2 * std::pow(std::sin(phi), 2));
    const double h = altitude() * 1000.0; // convert km to m

    const double x = (N + h) * std::cos(phi) * std::cos(lambda);
    const double y = (N + h) * std::cos(phi) * std::sin(lambda);
    const double z = (std::pow(b, 2) / std::pow(a, 2) * N + h) * std::sin(phi);

    return coordECEF(x, y, z);
}

double coordECEF::distanceTo(coordECEF point) {
    return std::sqrt(std::pow(point.x() - x(), 2) + std::pow(point.y() - y(), 2) + std::pow(point.z() - z(), 2));
}


#if defined(TESTING)
#include "gtest/gtest.h"

TEST(coord, coord) {
    coord p1{39.19704, 127.65702, 381.22697};
    ASSERT_DOUBLE_EQ (p1.m1(),  39.19704);
    ASSERT_DOUBLE_EQ (p1.m2(),  127.65702);
    ASSERT_DOUBLE_EQ (p1.m3(),  381.22697);
}

TEST(coordECEF, coordECEF) {
    coordECEF p1{39.19704, 127.65702, 381.22697};
    ASSERT_DOUBLE_EQ (p1.x(),  39.19704);
    ASSERT_DOUBLE_EQ (p1.y(),  127.65702);
    ASSERT_DOUBLE_EQ (p1.z(),  381.22697);
}

TEST(coordECEF, distanceTo) {
    coordECEF p1{1, 1, 0};
    coordECEF p2{2, 1, 2};
    ASSERT_NEAR (p1.distanceTo(p2), 2.236067977, 1.0e-6);
}

TEST(coordLLA, coordLLA) {
    coordLLA p1{39.19704, 127.65702, 381.22697};
    ASSERT_DOUBLE_EQ (p1.latitude(),  39.19704);
    ASSERT_DOUBLE_EQ (p1.longitude(),  127.65702);
    ASSERT_DOUBLE_EQ (p1.altitude(),  381.22697);
}

TEST(coordLLA, ecef) {
    coordLLA p1{39.19704, 127.65702, 381.22697};
    coordECEF p2 = p1.ecef();
    ASSERT_NEAR (p2.x(),  -3204329.5, 0.1);
    ASSERT_NEAR (p2.y(),  4152351.8, 0.1);
    ASSERT_NEAR (p2.z(),  4250224.6, 0.1);

    coordLLA p3{0.0, 0.0, 0.0};
    coordECEF p4 = p3.ecef();
    ASSERT_DOUBLE_EQ (p4.x(),  6378137.0); // a in conversion
    ASSERT_NEAR (p4.y(),  0.0, 1.0e-8);
    ASSERT_NEAR (p4.z(),  0.0, 1.0e-8);
    
    coordLLA p5{90.0, 0.0, 0.0};
    coordECEF p6 = p5.ecef();
    ASSERT_NEAR (p6.x(),  0.0, 1.0e-8);
    ASSERT_NEAR (p6.y(),  0.0, 1.0e-8);
    ASSERT_NEAR (p6.z(),  6356752.31424518, 1.0e-5); // b in conversion (12 significant digits)

    coordLLA p7{0.0, 90.0, 0.0};
    coordECEF p8 = p7.ecef();
    ASSERT_NEAR (p8.x(),  0.0, 1.0e-8);
    ASSERT_DOUBLE_EQ (p8.y(),  6378137.0); // a in conversion
    ASSERT_NEAR (p8.z(),  0.0, 1.0e-8);
    
    coordLLA p9{-90.0, 0.0, 0.0};
    coordECEF p10 = p9.ecef();
    ASSERT_NEAR (p10.x(),  0.0, 1.0e-8);
    ASSERT_NEAR (p10.y(),  0.0, 1.0e-8);
    ASSERT_NEAR (p10.z(),  -6356752.31424518, 1.0e-5); // b in conversion (12 significant digits)

    coordLLA p11{0.0, -90.0, 0.0};
    coordECEF p12 = p11.ecef();
    ASSERT_NEAR (p12.x(),  0.0, 1.0e-8);
    ASSERT_DOUBLE_EQ (p12.y(),  -6378137.0); // a in conversion
    ASSERT_NEAR (p12.z(),  0.0, 1.0e-8);
}

#endif // TESTING