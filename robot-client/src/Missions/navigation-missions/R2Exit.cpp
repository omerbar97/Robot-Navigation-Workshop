//
// Created by omer on 6/28/23.
//

#include "R2Exit.h"

R2Exit::R2Exit(Room *currentRoom, RobotWrapper *robot) {
    this->robot = robot;
    this->currentRoom = currentRoom;
    this->behavior = new ExitRoomBehavior(this->robot, currentRoom);
}

int R2Exit::doMission() {
    return behavior->execute();
}

R2Exit::~R2Exit() noexcept {
    delete(this->behavior);
}