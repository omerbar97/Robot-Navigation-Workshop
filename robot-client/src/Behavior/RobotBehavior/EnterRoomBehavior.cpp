//
// Created by omer on 5/8/23.
//

#include "EnterRoomBehavior.h"
#include "RotationBehavior.h"

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
    double forwardSpeed = 0.01;
    double turnSpeed = 0;
    double minDistance = 0.1;

    // TODO: think about bring the robot into the entry point of the room first

    /// move robot into doorstep in a straight line using a straight line behaviour
    navigateStraightLine(robot, this->goalRoom->getExitPoint(), forwardSpeed, turnSpeed, minDistance);

    /// move robot into the room's center using a rotation behaviour
    navigateStraightLine(robot, this->goalRoom->getCenterPoint(), forwardSpeed, turnSpeed, minDistance);

    return 0;
}

bool EnterRoomBehavior::avoidObstacles(double &forwardSpeed, double &turnSpeed) {
    return false;
}

