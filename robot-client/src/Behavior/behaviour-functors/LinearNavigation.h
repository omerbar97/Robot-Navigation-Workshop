//
// Created by ofirhelerman on 6/11/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_LINEARNAVIGATION_H
#define ROBOT_NAVIGATION_WORKSHOP_LINEARNAVIGATION_H


#include "../../Robot/RobotWrapper.h"
#include "../RobotBehavior/RotationBehavior.h"

using Point = std::pair<double, double>;

class LinearNavigation {


public:
    LinearNavigation() = default;
    ~LinearNavigation() = default;
    void operator () (RobotWrapper* robot, Point dest, double fSpeed, const double minDistance);

};


#endif //ROBOT_NAVIGATION_WORKSHOP_LINEARNAVIGATION_H