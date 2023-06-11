//
// Created by omer on 4/19/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
#define ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
#include <vector>
#include <string>
#include "../PathPlanning/Route.h"
#include "../Resources/Room.h"
#include "Navigatable.h"
#include "../Behavior/Mission.h"

class Navigation : public Mission {
private:

    // new members
    Behavior* behavior;

public:


    /**
     * constructor.
     * @param navigatable - the navigatable object that will be navigated.
     */
    Navigation(Navigatable* navigatable);

    /**
     * constructor. (with behavior) the behavior is the logic that the navigatable object will execute
     * will navigate the object to the given destination.
     * @param navigatable
     * @param behavior
     * @param currentPosition
     * @param destination
     */
    Navigation(Navigatable* navigatable, Behavior* behavior);

    /**
     * destructor.
     */
    ~Navigation();

    /**
     * set the behavior that will be executed when the navigatable object is navigating.
     * this is private going to call it from the setMission method.
     * @param behavior
     */
    void setBehavior(Behavior* behavior);


    // override method
    /**
     * set the mission of the navigatable object.
     * @param mission
     */
    void setMission(Behavior *behavior);

    /**
     * do the mission of the navigatable object.
     * @return
     */
     int doMission() {
        behavior->execute();
        return 0;
     }

};


#endif //ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
