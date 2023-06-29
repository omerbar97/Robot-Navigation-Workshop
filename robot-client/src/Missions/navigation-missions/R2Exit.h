//
// Created by omer on 6/28/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_R2EXIT_H
#define ROBOT_NAVIGATION_WORKSHOP_R2EXIT_H
#include "../Mission.h"
#include "../../Behavior/RobotBehavior/ExitRoomBehavior.h"

class R2Exit : public Mission{
private:
    RobotWrapper* robot;
    Behavior* behavior;

public:
    R2Exit(Room* currentRoom, RobotWrapper* robot);
    ~R2Exit();
    int doMission() override;

};


#endif //ROBOT_NAVIGATION_WORKSHOP_R2EXIT_H
