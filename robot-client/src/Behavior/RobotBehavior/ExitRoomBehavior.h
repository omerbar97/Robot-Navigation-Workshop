//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_EXITROOMBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_EXITROOMBEHAVIOR_H
#include "RobotBehavior.h"

class ExitRoomBehavior : public RobotBehavior{
public:

    /**
     * constructor
     * @param robot
     */
    ExitRoomBehavior(RobotWrapper* robot, std::pair<double, double> goalPoint);

    /**
     * navigation logic to navigate the robot when exiting the room
     */
    int execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_EXITROOMBEHAVIOR_H
