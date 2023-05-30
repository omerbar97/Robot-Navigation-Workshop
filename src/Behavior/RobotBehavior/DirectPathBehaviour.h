//
// Created by ofirhelerman on 5/29/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_DIRECTPATHBEHAVIOUR_H
#define ROBOT_NAVIGATION_WORKSHOP_DIRECTPATHBEHAVIOUR_H


#include "RobotBehavior.h"

class DirectPathBehaviour : public RobotBehavior {
protected:

    bool avoidObstacles(double &forwardSpeed, double &turnSpeed) override;


};


#endif //ROBOT_NAVIGATION_WORKSHOP_DIRECTPATHBEHAVIOUR_H
