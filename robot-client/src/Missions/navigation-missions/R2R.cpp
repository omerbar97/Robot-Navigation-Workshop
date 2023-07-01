//
// Created by shilopadael on 6/14/23.
//

#include "R2R.h"


R2R::R2R(Room *roomSource, Room *roomDest, RobotWrapper *robot, Algorithm *algorithm, MapGenerator *mapGenerator,
         bool withExit) {
    this->robot = robot;
    this->currentRoom = roomSource;
    this->nextRoom = roomDest;
    this->algorithm = algorithm;
    robot->update();
    this->tasks = vector<Behavior *>();
    Behavior *exit;
    if (withExit) {
        exit = new ExitRoomBehavior(this->robot, roomSource);
        this->tasks.push_back(exit);
    }

    route = new Route(algorithm, mapGenerator);
    route->setStartingPoint(roomSource->getEntryPoint());
    route->setGoalPoint(roomDest->getEntryPoint());
}

std::vector<std::pair<double, double>> R2R::getPath() {
    return this->path;
}

int R2R::doMission() {
    std::thread* t = nullptr;
    if(this->withExit) {
        R2Exit r2e = R2Exit(this->currentRoom, this->robot);
        t = new std::thread(&R2Exit::doMission, &r2e);
        t->detach();
    }
    try {
        route->createPath();
    } catch (std::exception &e) {
        // print some value
        std::cout << RED << "failed to calculate path from room id: " << this->currentRoom->getRoomId() << " to room id: "
                  << this->nextRoom->getRoomId() << COLOR_RESET << std::endl;

        throw std::exception();
    }
    path = route->getLatestPath();
    if (!path.empty()) {
        path.erase(path.begin());
    }
    this->tasks.push_back(new HallNavigateBehavior(this->robot, path));
    this->tasks.push_back(new EnterRoomBehavior(robot, this->nextRoom));
    int k;
    for (Behavior *task: tasks) {
        try {
            k = task->execute();
        } catch (std::exception &e) {
            // checking the room that failed
            std::string s = std::to_string(this->nextRoom->getRoomId());
            throw std::invalid_argument(s);
        }
        if (k != 0) {
            // error in the navigation
            return k;
        }
    }
    return 0;
}

R2R::~R2R() {
    // deleting all the memory
    delete (this->route);
    for (Behavior *b: this->tasks) {
        delete (b);
    }
    delete (this->algorithm);
}
