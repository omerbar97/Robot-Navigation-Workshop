//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_HALLNAVIGATEBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_HALLNAVIGATEBEHAVIOR_H
#include "RobotBehavior.h"
#include "RotationBehavior.h"
#include "../behaviour-functors/LinearNavigation.h"
using namespace std;
using Point = std::pair<double, double>;
class HallNavigateBehavior : public RobotBehavior {
protected:
    vector<Point> path;
    bool avoidObstacles(double &forwardSpeed, double &turnSpeed) override;

public:

    /**
     * constructor
     * @param robot
     */
    HallNavigateBehavior(RobotWrapper* robot, vector<Point>& path);

    ~HallNavigateBehavior() override = default;

    /**
     * navigation logic to navigate the robot inside the hall
     */
    int execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_HALLNAVIGATEBEHAVIOR_H
