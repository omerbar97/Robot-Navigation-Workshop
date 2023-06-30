//
// Created by omer on 5/8/23.
//

#include "ExitRoomBehavior.h"
#include "../behaviour-functors/RotateRobot.h"


ExitRoomBehavior::ExitRoomBehavior(RobotWrapper *robot, Room *goalRoom) :
RobotBehavior(robot, goalRoom->getEntryPoint()) {
    this->goalRoom = goalRoom;
}


int ExitRoomBehavior::execute() {
    // create a straight line behaviour to move the robot into the room and additional data
    LinearNavigation navigateStraightLine;
    RotateRobot rotateTowards;

    double forwardSpeed = 0.04;
    double minDistance = 0.1;

    // setting the robot sensitivity
    std::pair<int, int> angles;
    angles.first = 70;
    angles.second = 110;

    /// move robot into the room's center using a rotation behaviour
    rotateTowards(this->robot, this->goalRoom->getExitPoint());
    navigateStraightLine(this->robot, this->goalRoom->getExitPoint(), forwardSpeed, minDistance, angles, 0);

    /// move robot into doorstep in a straight line using a straight line behaviour
    rotateTowards(this->robot, this->goalRoom->getEntryPoint());
    navigateStraightLine(this->robot, this->goalRoom->getEntryPoint(), forwardSpeed, minDistance, angles, 0);

    return 0;
}
