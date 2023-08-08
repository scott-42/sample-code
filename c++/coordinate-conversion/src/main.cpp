// Copyright © 2020 R. Scott Gustafson. All rights reserved.

#include <iostream>
#include <limits>
#include <map>
#include <utility>
#include <algorithm>
#include "csv.h"
#include "coord.h"


struct velocities {
    std::vector<double> times;
    std::vector<double> speeds;
};

velocities calcVelocities(std::vector<csv::format>& data) {
    velocities vels;
    
    double previousSpeed = 0.0;
    double previousTime = data[0].time;
    coordLLA point{data[0].lat, data[0].lon, data[0].alt};
    coordECEF previousPoint = point.ecef();
    vels.times.push_back(previousTime);
    vels.speeds.push_back(previousSpeed);
    for (auto iter = data.begin() + 1; iter != data.end(); ++iter) {
        coordLLA c1{(*iter).lat, (*iter).lon, (*iter).alt};
        coordECEF c2 = c1.ecef();
        
        double speed = previousPoint.distanceTo(c2) / ((*iter).time - previousTime);
        vels.times.push_back((*iter).time);
        vels.speeds.push_back(speed);

        previousSpeed = speed;
        previousTime = (*iter).time;
        previousPoint = c2;
    }

    return vels;
}

double velocityAtTime(double time, velocities& vels) {
    // find the time just past the time reference
    auto timeIter = std::find_if(vels.times.begin(), vels.times.end(), [&](double i){return i >= time;});
    if ((timeIter == vels.times.end() && *timeIter >= time) || timeIter == vels.times.begin())
        return 0.0; // if we hit the end or the beginning something is wrong
    // find the time before and after the time reference
    double t2 = *timeIter--;
    double t1 = *timeIter;
    // find the same speeds that match the times
    auto speedIter = vels.speeds.begin() + (timeIter - vels.times.begin());
    double s1 = *speedIter++;
    double s2 = *speedIter;

    // using simple linear interpolation
    return (s2 - s1) * ((time - t1)/(t2 - t1)) + s1;
}

int main(int argc, char** argv) {

    csv file;

    velocities vels = calcVelocities(file.m_data);

    std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << "Time: 1532334000 Velocity: " << velocityAtTime(1532334000, vels) << std::endl;
    std::cout << "Time: 1532335268 Velocity: " << velocityAtTime(1532335268, vels) << std::endl;

    return 0;
}