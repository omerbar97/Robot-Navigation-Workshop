//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ENTERROOMBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_ENTERROOMBEHAVIOR_H
#include "RobotBehavior.h"

class EnterRoomBehavior : public RobotBehavior {
public:

    /**
     * constructor
     * @param robot
     */
    EnterRoomBehavior(RobotWrapper* robot);

    /**
     * navigation logic to navigate the robot when entering the room
     */
    int execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ENTERROOMBEHAVIOR_H
