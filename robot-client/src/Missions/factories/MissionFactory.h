//
// Created by ofirhelerman on 6/15/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_MISSIONFACTORY_H
#define ROBOT_NAVIGATION_WORKSHOP_MISSIONFACTORY_H

#include <vector>
#include "../Mission.h"

class MissionFactory {
public:
    virtual Mission* createMission(void* args) = 0;
};

#endif //ROBOT_NAVIGATION_WORKSHOP_MISSIONFACTORY_H
