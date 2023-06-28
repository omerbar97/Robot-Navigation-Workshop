//
// Created by shilopadael on 6/14/23.
//

#include "R2R.h"


R2R::R2R(Room* roomSource, Room *roomDest, RobotWrapper *robot, Algorithm* algorithm, MapGenerator* mapGenerator) {
    this->robot = robot;
    this->currentRoom = roomSource;
    this->nextRoom = roomDest;
    this->algorithm = algorithm;
    robot->update();
    this->tasks = vector<Behavior*>();

    Behavior* exit = new ExitRoomBehavior(this->robot, roomSource);
    this->tasks.push_back(exit);

    route = new Route(algorithm, mapGenerator);
    route->setStartingPoint(roomSource->getEntryPoint());
    route->setGoalPoint(roomDest->getEntryPoint());
    try {
        route->createPath();
    } catch (std::exception &e) {
        // print some value
        std::cout << RED << "failed to calculate path from room id: " << roomSource->getRoomId() << " to room id: " << roomDest->getRoomId() << std::endl;
        delete(exit);
        delete(this);
        throw std::exception();
    }
    path = route->getLatestPath();
    if (!path.empty()) {
        path.erase(path.begin());
    }
    this->tasks.push_back(new HallNavigateBehavior(this->robot, path));

    this->tasks.push_back(new EnterRoomBehavior(robot, roomDest));

}

std::vector<std::pair<double, double>> R2R::getPath() {
    return this->path;
}

int R2R::doMission() {
    for (Behavior* task : tasks) {
        try {
            task->execute();
        } catch (ompl::Exception e) {
            // recalculate
        }
    }
    return 0;
}

R2R::~R2R() {
    // deleting all the memory
    delete(this->route);
    for(Behavior* b : this->tasks) {
        delete(b);
    }
    delete(this->currentRoom);
    delete(this->nextRoom);
    delete(this->algorithm);
}
