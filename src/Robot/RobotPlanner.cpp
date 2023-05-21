//
// Created by omer on 5/5/23.
//

#include "RobotPlanner.h"

RobotPlanner::RobotPlanner(std::string roomConfigPath, RobotWrapper* robotWrapper, MapGenerator* mapGenerator) {
    std::pair<double, double> defPoint = std::make_pair(0, 0);
    this->roomConfigPath = roomConfigPath;
    this->robotWrapper = robotWrapper;
    RoomsHandler roomsHandler(roomConfigPath, std::vector<int>{1,2,3,4,5,6,7,8,9,10});
    this->rooms = roomsHandler.getRooms();
    this->route = new Route(new RRTStarAlgorithm(), mapGenerator);
    this->robotBehaviorFactory = new RobotBehaviorFactory(this->robotWrapper, defPoint);
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
    //TODO :make sure that in the room clas there is  option to push a room.
    //set the first two point, the first point is always the robot Postion, and the end point is to nhe next point
    while(!this->rooms.empty()) {

        //get the next room
        Room room = this->rooms.front();
        this->rooms.erase(this->rooms.begin());

        goToPoint(room.getEntryPoint());
        goToPoint(room.getExitPoint());
        //got to the next room
    }
}

void RobotPlanner::goToPoint(std::pair<double, double> point) {
    //TODO:: update the position after merge with omer branch.
    std::pair robotPosition=  std::make_pair(this->robotWrapper->getPos()->GetXPos(), this->robotWrapper->getPos()->GetYPos());
    this->route->setStartingPoint(robotPosition);

    this->route->setGoalPoint(point);
    this->route->createPath();

    // getting route
    auto matrixPath = route->matrixPoint();

    //execute the path
    for (auto point : matrixPath) {
        //TODO:: make sure that the robot position is the position we need.
        //set start point of the factory
        //TODO:: update the position after merge with omer branch.
        robotPosition=  std::make_pair(this->robotWrapper->getPos()->GetXPos(), this->robotWrapper->getPos()->GetYPos());
        this->robotBehaviorFactory->setStartPoint(robotPosition);
        //set the end point of the factory
        this->robotBehaviorFactory->setGoalPoint(point);
        //execute the behavior
        this->robotBehaviorFactory->createBehavior()->execute();
    }

}
