//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_HALLNAVIGATEBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_HALLNAVIGATEBEHAVIOR_H
#include "RobotBehavior.h"

class HallNavigateBehavior : public RobotBehavior {
protected:

    void avoidObstacles(double &forwardSpeed, double &turnSpeed) override;

public:

    /**
     * constructor
     * @param robot
     */
    HallNavigateBehavior(RobotWrapper* robot, std::pair<double, double> goalPoint);

    ~HallNavigateBehavior();

    /**
     * navigation logic to navigate the robot inside the hall
     */
    int execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_HALLNAVIGATEBEHAVIOR_H
