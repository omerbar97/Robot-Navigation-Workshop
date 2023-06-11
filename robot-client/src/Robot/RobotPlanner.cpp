//
// Created by omer on 5/5/23.
//

#include "RobotPlanner.h"

RobotPlanner::RobotPlanner(std::string roomConfigPath, RobotWrapper* robotWrapper, MapGenerator* mapGenerator) {
    std::pair<double, double> defPoint = std::make_pair(0, 0);
    this->roomConfigPath = roomConfigPath;
    this->robotWrapper = robotWrapper;
    RoomsHandler roomsHandler(roomConfigPath, std::vector<int>{2,1});
    this->rooms = roomsHandler.getRooms();
    this->route = new Route(new RRTStarAlgorithm(), mapGenerator);
//    this->robotBehaviorFactory = new RobotBehaviorFactory(this->robotWrapper, defPoint);
}
//TODO: update the room file
std::vector<Room> RobotPlanner::getRooms() const {
    return this->rooms;
}

/**
 * set the rooms of the robot
 * @param rooms - the rooms to set
 */
int RobotPlanner::executePlan() {
    //set the first two points, the first point is always the robot Postion, and the end point is to nhe next point
    for(int i = 0; i < this->rooms.size(); i++) {
        //get the next room
        Room room = this->rooms[i];
        goToPoint(room.getEntryPoint());


        //create a behavior of entryRoom.


        goToPoint(room.getExitPoint());

    }
}

void RobotPlanner::goToPoint(std::pair<double, double> point) {
    //TODO:: update the position after merge with omer branch.
    std::pair<double, double> start = robotWrapper->getCurrentPosition();
    this->route->setStartingPoint(start);
    this->route->setGoalPoint(point);

    this->route->createPath();

    // getting route

    std::vector<std::pair<double, double> > path = route->getLatestPath();

    //execute the path
    for(int i = 1; i < path.size(); i++) {
        //rotation to the point
        RotationBehavior rotationBehavior(robotWrapper, path[i]);
        rotationBehavior.execute();


        HallNavigateBehavior hallNavigateBehavior(robotWrapper, path[i]);
        hallNavigateBehavior.execute();


    }

}
