//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_HALLNAVIGATEBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_HALLNAVIGATEBEHAVIOR_H
#include "RobotBehavior.h"

class HallNavigateBehavior : public RobotBehavior {
public:

    /**
     * constructor
     * @param robot
     */
    HallNavigateBehavior(RobotWrapper* robot);

    /**
     * navigation logic to navigate the robot inside the hall
     */
    void execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_HALLNAVIGATEBEHAVIOR_H
