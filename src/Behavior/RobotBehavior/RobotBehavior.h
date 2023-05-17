//
// Created by omer on 5/9/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTBEHAVIOR_H
#include "../../Robot/RobotWrapper.h"
#include "../Behavior.h"
#include <vector>

/**
 * this is a middleware class between the behavior to the actual robotBehaviors,
 * each class the implements this behavior needs to implement the logic part in the execute.
 */
class RobotBehavior : public Behavior {
protected:
    RobotWrapper* robot;
    std::pair<double, double> goalPoint;


public:
    RobotBehavior(RobotWrapper* robot, std::pair<double, double> goalPoint);
    virtual ~RobotBehavior() = default;

    // the virtual method is still virtual
    virtual int execute() = 0;

};

#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTBEHAVIOR_H
