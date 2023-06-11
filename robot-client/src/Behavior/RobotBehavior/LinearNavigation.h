//
// Created by ofirhelerman on 6/11/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_LINEARNAVIGATION_H
#define ROBOT_NAVIGATION_WORKSHOP_LINEARNAVIGATION_H


#include "../../Robot/RobotWrapper.h"
#include "RotationBehavior.h"

using Point = std::pair<double, double>;

class LinearNavigation {
private:
    double calcDistance(double x1, double y1, double x2, double y2);


public:
    LinearNavigation() = default;
    ~LinearNavigation() = default;
    void operator () (RobotWrapper* robot, Point dest, double fSpeed, double tSpeed, const double minDistance);

};


#endif //ROBOT_NAVIGATION_WORKSHOP_LINEARNAVIGATION_H
