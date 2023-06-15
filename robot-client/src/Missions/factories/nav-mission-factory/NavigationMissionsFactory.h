//
// Created by ofirhelerman on 6/15/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_NAVIGATIONMISSIONSFACTORY_H
#define ROBOT_NAVIGATION_WORKSHOP_NAVIGATIONMISSIONSFACTORY_H


#include "../../Mission.h"
#include "../../../PathPlanning/Algorithm/Algorithm.h"

class NavigationMissionsFactory {
public:
    NavigationMissionsFactory() = default;
    ~NavigationMissionsFactory() = default;
    Mission* createR2RMission(Room* roomSource, Room* roomDest, RobotWrapper* robot, Algorithm* algorithm);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_NAVIGATIONMISSIONSFACTORY_H
