//
// Created by omer on 5/17/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROTATIONBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_ROTATIONBEHAVIOR_H
#include "RobotBehavior.h"

class RotationBehavior : public RobotBehavior{
public:

    /**
     * constructor
     * @param robot
     */
    RotationBehavior(RobotWrapper* robot, std::pair<double, double> goalPoint);

    ~RotationBehavior();

    /**
     * navigation logic to navigate the robot inside the hall
     */
    int execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROTATIONBEHAVIOR_H
