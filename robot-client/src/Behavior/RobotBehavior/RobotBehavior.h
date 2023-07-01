//
// Created by omer on 5/9/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTBEHAVIOR_H
#include "../../Robot/RobotWrapper.h"
#include "../Behavior.h"
#include <vector>


/**
 * RobotBehavior is an interface for all the robot behaviors.
 * It extern the method execute() which is the main method for the behavior.
 */
class RobotBehavior : public Behavior {
protected:
    RobotWrapper* robot;
    std::pair<double, double> goalPoint;

public:

    /**
     * this is the function that needs to be implemented by the robot behavior.
     * @return
     */
    virtual int execute() = 0;

    /**
     * constructor
     * @param robot the robot wrapper
     * @param goalPoint the point to navigate to
     */
    RobotBehavior(RobotWrapper* robot, std::pair<double, double> goalPoint);
    virtual ~RobotBehavior() = default;

};

#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTBEHAVIOR_H
