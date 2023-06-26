//
// Created by omer on 6/26/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_AVOIDOBSTACLE_H
#define ROBOT_NAVIGATION_WORKSHOP_AVOIDOBSTACLE_H
#include "../../Robot/RobotWrapper.h"
#include "../RobotBehavior/RotationBehavior.h"
using Point = std::pair<double, double>;

class AvoidObstacle {

public:

    void operator()(RobotWrapper* robot, Point dest, double fSpeed, const double minDistance);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_AVOIDOBSTACLE_H
