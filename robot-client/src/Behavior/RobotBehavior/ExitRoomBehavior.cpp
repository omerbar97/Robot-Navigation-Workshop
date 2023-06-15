//
// Created by omer on 5/8/23.
//

#include "ExitRoomBehavior.h"



ExitRoomBehavior::ExitRoomBehavior(RobotWrapper *robot, Room *goalRoom) :
RobotBehavior(robot, goalRoom->getEntryPoint()) {
    this->goalRoom = goalRoom;
}

bool ExitRoomBehavior::avoidObstacles(double &forwardSpeed, double &turnSpeed) {
    return false;
}

int ExitRoomBehavior::execute() {
    // create a straight line behaviour to move the robot into the room and additional data
    LinearNavigation navigateStraightLine;
    double forwardSpeed = 0.04;
    double turnSpeed = 0;
    double minDistance = 0.1;

    /// move robot into the room's center using a rotation behaviour
    navigateStraightLine(robot, this->goalRoom->getExitPoint(), forwardSpeed, turnSpeed, minDistance);

    /// move robot into doorstep in a straight line using a straight line behaviour
    navigateStraightLine(robot, this->goalRoom->getEntryPoint(), forwardSpeed, turnSpeed, minDistance);

    return 0;
}
