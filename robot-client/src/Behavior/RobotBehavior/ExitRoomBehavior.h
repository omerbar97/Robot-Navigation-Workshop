//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_EXITROOMBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_EXITROOMBEHAVIOR_H
#include "RobotBehavior.h"
#include "../behaviour-functors/LinearNavigation.h"
#include "../../Resources/Room.h"


class ExitRoomBehavior : public RobotBehavior{

protected:
    bool avoidObstacles(double &forwardSpeed, double &turnSpeed) override;
    Room* goalRoom;


public:

    /**
     * constructor
     * @param robot the robot wrapper
     * @param goalPoint the point to navigate to
     */
    ExitRoomBehavior(RobotWrapper* robot, Room *goalRoom);

    /**
     * navigation logic to navigate the robot when exiting the room.
     *
     * @Assumptions
     * 1. the robot is currently near the center point of the room
     */
    int execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_EXITROOMBEHAVIOR_H
