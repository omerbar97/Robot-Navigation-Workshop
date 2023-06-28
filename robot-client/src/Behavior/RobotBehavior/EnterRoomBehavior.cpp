//
// Created by omer on 5/8/23.
//

#include "EnterRoomBehavior.h"


EnterRoomBehavior::EnterRoomBehavior(RobotWrapper *robot, Room* goalRoom) :
RobotBehavior(robot, goalRoom->getCenterPoint()) {
    this->goalRoom = goalRoom;
}

EnterRoomBehavior::~EnterRoomBehavior()= default;

/**
 * navigation logic to navigate the robot inside the room
 *
 * Assumptions:
 * 1. the robot is currently near the entry point of the room
 */
int EnterRoomBehavior::execute() {

    // create a straight line behaviour to move the robot into the room and additional data
    LinearNavigation navigateStraightLine;
    RotateRobot rotateTowards;
    double forwardSpeed = 0.04;
    double minDistance = 0.1;

    // setting the robot sensitivity
    std::pair<int, int> angles;
    angles.first = 70;
    angles.second = 110;
    // TODO: think about bring the robot into the entry point of the room first

    /// move robot into doorstep in a straight line using a straight line behaviour
    rotateTowards(this->robot, this->goalRoom->getExitPoint());
    navigateStraightLine(robot, this->goalRoom->getExitPoint(), forwardSpeed, minDistance, angles, 0);

    /// move robot into the room's center using a rotation behaviour
    rotateTowards(this->robot, this->goalRoom->getCenterPoint());
    navigateStraightLine(robot, this->goalRoom->getCenterPoint(), forwardSpeed, minDistance, angles, 0);

    return 0;
}



