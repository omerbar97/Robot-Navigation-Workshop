//
// Created by shilopadael on 6/14/23.
//

#include "NavigationMission.h"


NavigationMission::NavigationMission(Room* roomSource, Room *roomDest, RobotWrapper *robot) {
    this->robot = robot;
    this->roomSource = roomSource;
    this->roomDest = roomDest;

}

int NavigationMission::doMission() {
    robot->update();
    std::vector<Behavior*> vector;

//    vector.push_back(new ExitRoomBehavior(this->robot, this->roomSource));
    vector.push_back(new HallNavigateBehavior(robot, roomDest->getEntryPoint()));
//    vector.push_back(new EnterRoomBehavior(robot, this->roomDest));

    for (Behavior* task : vector) {
        task->execute();
    }
}
