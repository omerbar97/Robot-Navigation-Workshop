//
// Created by shilopadael on 6/14/23.
//

#include "R2R.h"
#include "../../PathPlanning/Route.h"


R2R::R2R(Room* roomSource, Room *roomDest, RobotWrapper *robot) {
    this->robot = robot;

    robot->update();
    std::vector<Behavior*> vector;

    vector.push_back(new ExitRoomBehavior(this->robot, roomSource));
    Route*
    Route* route = new Route(this->roomSource->getEntryPoint(), roomDest->getEntryPoint());
    vector.push_back(new EnterRoomBehavior(robot, roomDest));


}

int R2R::doMission() {
    for (Behavior* task : vector) {
        task->execute();
    }
}
