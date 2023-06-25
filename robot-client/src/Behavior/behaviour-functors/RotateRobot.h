//
// Created by ofirhelerman on 6/15/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROTATEROBOT_H
#define ROBOT_NAVIGATION_WORKSHOP_ROTATEROBOT_H


#include "../../Robot/RobotWrapper.h"
using Point = std::pair<double, double>;
class RotateRobot {
public:
    RotateRobot() = default;
    ~RotateRobot() = default;
    void operator () (RobotWrapper* robot, const Point& goalPoint);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROTATEROBOT_H
