//
// Created by shilopadael on 6/14/23.
//

#include "R2R.h"
#include "../../PathPlanning/Route.h"


R2R::R2R(Room* roomSource, Room *roomDest, RobotWrapper *robot, Algorithm* algorithm, MapGenerator* mapGenerator) {
    this->robot = robot;

    robot->update();
    this->tasks = vector<Behavior*>();

    this->tasks.push_back(new ExitRoomBehavior(this->robot, roomSource));

    auto* route = new Route(algorithm, mapGenerator);
    route->setStartingPoint(roomSource->getEntryPoint());
    route->setGoalPoint(roomDest->getEntryPoint());
    route->createPath();
    vector<Point> path = route->getLatestPath();
    if (!path.empty()) {
        path.erase(path.begin());
    }
    this->tasks.push_back(new HallNavigateBehavior(this->robot, path));

    this->tasks.push_back(new EnterRoomBehavior(robot, roomDest));


}

int R2R::doMission() {
    for (Behavior* task : tasks) {
        task->execute();
    }
}
