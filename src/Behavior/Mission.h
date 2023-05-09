//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_MISSION_H
#define ROBOT_NAVIGATION_WORKSHOP_MISSION_H

#include "Behavior.h"

/**
 * interface for a mission, a mission can be sending data or navigating.
 */
class Mission {
protected:

    Behavior *behavior;

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
     */
    virtual void doMission() = 0;

    /**
     * each mission has a behavior, this method sets the behavior for the mission.
     * @param behavior
     */
    virtual void setMission(Behavior *behavior) = 0;

};

#endif //ROBOT_NAVIGATION_WORKSHOP_MISSION_H
