//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_EXITROOMBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_EXITROOMBEHAVIOR_H
#include "RobotBehavior.h"
#include "../behaviour-functors/LinearNavigation.h"
#include "../../Resources/Room.h"

/**
 * this class responsible for navigating the robot out of the room.
 */
class ExitRoomBehavior : public RobotBehavior{

protected:
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
     *  - the robot is currently near the center point of the room
     */
    int execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_EXITROOMBEHAVIOR_H
