//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_NAVIGATABLE_H
#define ROBOT_NAVIGATION_WORKSHOP_NAVIGATABLE_H
#include <vector>
#include "../Behavior/Behavior.h"

/**
 * interface for any object that can be navigated, a.k.a robot
 */
class Navigatable {
public:

    /**
     * destructor for the navigatable. (for the inheritance)
     */
    virtual ~Navigatable() = default;

    /**
     * travel to a given path by given coordinates, using the robot's navigation system.
     * @param path - the path to travel the points are in Stage Point
     */
    virtual void travelTo(std::vector<std::pair<double, double>> path) = 0;

    /**
     * get the current location of the navigatable object
     * @return the current location of the navigatable object
     */
    virtual std::pair<double, double> getCurrentLocation() = 0;

    /**
     * set the behavior of the navigatable object. the behavior is the logic that the navigatable object will execute
     * @param behavior - can be for example RobotBehavior.
     */
    virtual void setBehavior(Behavior* behavior) = 0;



};


#endif //ROBOT_NAVIGATION_WORKSHOP_NAVIGATABLE_H
