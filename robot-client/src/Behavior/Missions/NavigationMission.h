//
// Created by shilopadael on 6/14/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_NAVIGATIONMISSION_H
#define ROBOT_NAVIGATION_WORKSHOP_NAVIGATIONMISSION_H

#include "../Mission.h"
#include "../RobotBehavior/EnterRoomBehavior.h"
#include "../RobotBehavior/HallNavigateBehavior.h"
#include "../RobotBehavior/ExitRoomBehavior.h"

using namespace std;
using Point = std::pair<double, double>;
class NavigationMission : public Mission {
private:
    Room* roomSource;
    Room* roomDest;

    RobotWrapper* robot;


public:
    NavigationMission(Room* roomSource, Room* roomDest, RobotWrapper* robot);

    int doMission() override;

};



#endif //ROBOT_NAVIGATION_WORKSHOP_NAVIGATIONMISSION_H
