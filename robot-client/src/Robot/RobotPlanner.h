//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
#include <vector>
#include "../Resources/Room.h"
#include "../Resources/RoomsHandler.h"
#include "RobotWrapper.h"
#include "../PathPlanning/Route.h"
#include "../Resources/MapGenerator.h"
#include "../PathPlanning/Algorithm/RRTStarAlgorithm.h"
#include "../Behavior/Factory/RobotBehaviorFactory.h"



//TODO: update the room file
class RobotPlanner {
private:
    std::vector<Room> rooms;
    std:: string roomConfigPath;
    RobotWrapper *robotWrapper;
    Route* route;
    MapGenerator* mapGenerator;
    RobotBehaviorFactory* robotBehaviorFactory;

    void goToPoint(std::pair<double, double> point);

public:
    RobotPlanner(std::string roomConfigPath, RobotWrapper* robotWrapper, MapGenerator* mapGenerator);
    std::vector<Room> getRooms() const;
    std::vector<Room> setRooms(std::vector<Room> rooms);
    int executePlan();



};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
