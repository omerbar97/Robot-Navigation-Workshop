//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_MISSION_H
#define ROBOT_NAVIGATION_WORKSHOP_MISSION_H

#include "../Behavior/Behavior.h"
#include "../Robot/RobotWrapper.h"
#include "../Resources/Room.h"




enum class MissionType {
    NAVIGATION,
    INFORM
};

/**
 * interface for a mission, a mission can be sending data or navigating.
 */
class Mission {

protected:
    Room* currentRoom;
    Room* nextRoom;
public:

    /**
     * default constructor for the mission.
     */
    Mission() = default;

    /**
     * virtual destructor for the mission. (for the polymorphism)
     */
    virtual ~Mission() = default;

    /**
     * this method executes the mission.
     * return 0 mission accomplished
     * return 1 robot encounter obstacle
     * return 2 robot encounter wall
     */
    virtual int doMission() = 0;


};

#endif //ROBOT_NAVIGATION_WORKSHOP_MISSION_H
