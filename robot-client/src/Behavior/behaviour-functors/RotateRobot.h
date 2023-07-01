//
// Created by ofirhelerman on 6/15/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROTATEROBOT_H
#define ROBOT_NAVIGATION_WORKSHOP_ROTATEROBOT_H


#include "../../Robot/RobotWrapper.h"
using Point = std::pair<double, double>;

/**
 * RotateRobot is a functor that rotates the robot to a given destination.
 */
class RotateRobot {
public:
    // Default constructor.
    RotateRobot() = default;
    // Default destructor.
    ~RotateRobot() = default;

    /**
     * function: operator()
     * --------------------
     * This function rotates the robot to a given destination.
     * @param robot - the robot to rotate.
     * @param goalPoint - the destination to rotate to.
     */
    void operator () (RobotWrapper* robot, const Point& goalPoint);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROTATEROBOT_H
