//
// Created by omer on 6/28/23.
//

#include "CalculateTime.h"

double CalculateTime::operator()(std::vector<std::pair<double, double>> path, double robotSpeed) {
    // calculate the time to reach the point with the given speed

    // time X speed = road

    // calculating the linear distance between the path

    // distance = sqrt((x1 -x2)^2 + (y1-y2)^2)
    double distance = 0;
    for(int i = 1; i < path.size(); i++) {
        std::pair src = path[i - 1];
        std::pair dest = path[i];
        distance += sqrt(pow((src.first - dest.first), 2) + pow((src.second - dest.second), 2));
    }

    // calculating time in seconds

    // time X speed = road
    // time = road / speed

    double time = distance / robotSpeed;
    return time;

}
