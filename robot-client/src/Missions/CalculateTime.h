//
// Created by omer on 6/28/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
#define ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
#include "Mission.h"

class CalculateTime : public Mission {
public:
    CalculateTime() = default;
    ~CalculateTime() = default;
    double operator()(std::vector<std::pair<double, double>> path, double robotSpeed);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
