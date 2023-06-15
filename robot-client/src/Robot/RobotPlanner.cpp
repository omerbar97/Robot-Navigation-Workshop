//
// Created by omer on 5/5/23.
//

#include "RobotPlanner.h"

RobotPlanner::RobotPlanner(const string& roomConfigPath, RobotWrapper* robotWrapper, MapGenerator* mapGenerator) {
    std::pair<double, double> defPoint = std::make_pair(0, 0);
    this->robotWrapper = robotWrapper;
    this->mapGenerator = mapGenerator;
    this->route = new Route(new RRTStarAlgorithm(), this->mapGenerator);
    this->roomsContainer = new RoomsContainer(roomConfigPath);
//    this->robotBehaviorFactory = new RobotBehaviorFactory(this->robotWrapper, defPoint);
}

RobotPlanner::~RobotPlanner() = default;

/**
 * plan the inform mission
 * @param roomsIDs - the order of the rooms to visit
 */
void RobotPlanner::planInformMission(const vector<string>& roomsIDs) {
    // currently, the function assumes that inform mission is only to move between rooms.

    // if inside a room -
    // if inside if the first room - then inform the person in the room
    // if inside any other room - then navigate regularly, but first exit the room

    // if in the hallway - navigate to the next room regularly


}


void RobotPlanner::planNavigationMission(const vector<string>& roomsIDs) {
    // assumes that the robot starts inside a room
    // creating a plan that will look like this:
    // 1. navigate to the exit point of the current room
    // 2. navigate to the entry point of the next room
    // 3. enter the next room
    // 4. repeat 1-3 until the last room
    // note : in the future, it will use a factory to create the behaviors
    //        however for now, it will be done manually

    //TODO:: plan priority queue of MissionType and parameters
    for(int i = 0; i < roomsIDs.size() - 1; i++) {

        Room* currentRoom = this->roomsContainer->getRoomById(stoi(roomsIDs.at(i)));
        Room* nextRoom = this->roomsContainer->getRoomById(stoi(roomsIDs.at(i + 1)));
        Mission* mission = new NavigationMission(currentRoom, nextRoom, this->robotWrapper);
        this->currentPlan.push(mission);


        //get the next room
//        Room* room = this->roomsContainer->getRoomById(stoi(roomNum));
//        Mission * mission = new NavigationMission((this->robotWrapper), room);
//        this->currentPlan.push(mission);
    }


//    for (int i = 0; i < roomsIDs.size() - 2; i++) {
//        try {
//            int source = stoi(roomsIDs.at(i));
//            int destination = stoi(roomsIDs.at(i + 1));
//            this->currentPlan.push_back(new ExitRoomBehavior(this->robotWrapper,
//                                                             this->roomsContainer->getRoomById(source)));
//
//            this->currentPlan.push_back(new HallNavigateBehavior(this->robotWrapper,
//                                                                 this->roomsContainer->getRoomById(destination)->
//                                                                 getEntryPoint()));
//            this->currentPlan.push_back(new EnterRoomBehavior(this->robotWrapper,
//                                                              this->roomsContainer->getRoomById(destination + 1)));
//
//        } catch ( const exception& e) {
//            cout << "error: " << e.what() << endl;
//            exit(1);
//        }
//    }

}

void RobotPlanner::plan(const MissionType& mission, const vector<std::string> &parameters) {
    switch (mission) {
        case MissionType::NAVIGATION:
            planNavigationMission(parameters);
            break;
        case MissionType::INFORM:
            planInformMission(parameters);
            break;
        default:
            cout << "mission type not supported" << endl;
            exit(1);
    } 
}

/**
 * set the rooms of the robot
 * @param rooms - the rooms to set
 */
int RobotPlanner::executePlan() {
    while(this->currentPlan.size() > 0) {
        // get the next mission
        Mission* mission = this->currentPlan.front();
        // delete the mission from the queue
        this->currentPlan.pop();
        // do the mission
        mission->doMission();
        // delete the mission
        delete mission;
    }
    return 0;
}



//    //set the first two points, the first point is always the robot Postion, and the end point is to nhe next point
//    for(int i = 0; i < this->rooms.size(); i++) {
//        //get the next room
//        Room room = this->rooms[i];
//        goToPoint(room.getEntryPoint());
//
//
//        //create a behavior of entryRoom.
//
//
//        goToPoint(room.getExitPoint());
//
//    }

//void RobotPlanner::goToPoint(std::pair<double, double> point) {
//    //TODO:: update the position after merge with omer branch.
//    std::pair<double, double> start = robotWrapper->getCurrentPosition();
//    this->route->setStartingPoint(start);
//    this->route->setGoalPoint(point);
//
//    this->route->createPath();
//
//    // getting route
//
//    std::vector<std::pair<double, double> > path = route->getLatestPath();
//
//    //execute the path
//    for(int i = 1; i < path.size(); i++) {
//        //rotation to the point
//        RotationBehavior rotationBehavior(robotWrapper, path[i]);
//        rotationBehavior.execute();
//
//
//        HallNavigateBehavior hallNavigateBehavior(robotWrapper, path[i]);
//        hallNavigateBehavior.execute();
//
//
//    }
//
//}
