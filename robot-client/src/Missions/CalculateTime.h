//
// Created by omer on 6/28/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
#define ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
#include "Mission.h"

class CalculateTime : public Mission {
private:
    std::vector<std::pair<double, double>>* path;
    double robotSpeed;
    double time;

public:
    CalculateTime(std::vector<std::pair<double, double>>* path, double robotSpeed);
    ~CalculateTime();

    int doMission() override;

    double getTime();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
