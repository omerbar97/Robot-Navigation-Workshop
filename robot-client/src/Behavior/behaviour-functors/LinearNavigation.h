//
// Created by ofirhelerman on 6/11/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_LINEARNAVIGATION_H
#define ROBOT_NAVIGATION_WORKSHOP_LINEARNAVIGATION_H


#include "../../Robot/RobotWrapper.h"
#include <boost/bind/bind.hpp>
#include "AvoidObstacle.h"

using namespace boost::placeholders;
using Point = std::pair<double, double>;

/**
 * LinearNavigation is a functor that navigates the robot to a given destination in a linear path.
 */
class LinearNavigation {
private:

public:
    // Default constructor.
    LinearNavigation() = default;
    // Default destructor.
    ~LinearNavigation() = default;

    /**
     * function: operator()
     * --------------------
     * This function navigates the robot to a given destination in a linear path.
     * @param robot - the robot to navigate.
     * @param dest - the destination to navigate to.
     * @param fSpeed - the speed to navigate with, forward speed.
     * @param minDistance - the minimum distance to keep from obstacles.
     * @param angles - the angles to navigate with.
     * @param depth - the depth of the recursion.
     */
    void operator () (RobotWrapper* robot, Point dest, double fSpeed, const double minDistance, std::pair<int, int> angles, int depth);

};


#endif //ROBOT_NAVIGATION_WORKSHOP_LINEARNAVIGATION_H
