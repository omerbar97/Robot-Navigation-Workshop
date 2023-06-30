//
// Created by ofirhelerman on 6/30/23.
//

#include "PathCreator.h"
#include "../../PathPlanning/Route.h"

PathCreator::PathCreator(Point startPoint, int startRoomID, Point endPoint, int goalRoomID, MapGenerator *map,
                         MissionPathList *path, int cellID) {
    this->startPoint = startPoint;
    this->goalPoint = endPoint;
    this->map = map;
    this->path = path;
    this->cellID = cellID;
    this->startRoomID = startRoomID;
    this->goalRoomID = goalRoomID;
}

void PathCreator::operator()() {
    Algorithm* algorithm = new RRTStarAlgorithm();
    auto* route = new Route(algorithm, this->map);
    route->setStartingPoint(this->startPoint);
    route->setGoalPoint(this->goalPoint);

    try {
        route->createPath();
    } catch (std::exception &e) {
        // print some value
        std::cout << RED << "failed to calculate path from room id: " << this->startRoomID << " to room id: "
                  << this->goalRoomID << COLOR_RESET << std::endl;
        throw std::exception();
    }

    std::vector<std::pair<double, double>> r2rPath = route->getLatestPath();
    if (!r2rPath.empty()) {
        r2rPath.erase(r2rPath.begin());
    }

    this->path->at(this->cellID) = r2rPath;
}
