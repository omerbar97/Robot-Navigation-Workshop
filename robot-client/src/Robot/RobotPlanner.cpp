//
// Created by omer on 5/5/23.
//

#include "RobotPlanner.h"


RobotPlanner::RobotPlanner(const string& roomConfigPath, RobotWrapper* robotWrapper, MapGenerator* map) {
    this->robotWrapper = robotWrapper;
    this->roomsContainer = new RoomsContainer(roomConfigPath);
    this->map = map;
    this->isInPlan = false;
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


void RobotPlanner::planNavigationMission(vector<string>& roomsIDs) {
    // assumes that the robot starts inside a room
    //TODO:: plan priority queue of MissionType and parameters
    int counter = 0;
    Mission* mission;
    for(int i = 0; i < roomsIDs.size() - 1; i++) {
        Room *currentRoom = this->roomsContainer->getRoomById(stoi(roomsIDs.at(i)));
        Room *nextRoom = this->roomsContainer->getRoomById(stoi(roomsIDs.at(i + 1)));
        try {
            mission = new R2R(currentRoom, nextRoom, this->robotWrapper,
                                       new RRTStarAlgorithm(), this->map);
        } catch (std::exception &e) {
            if(counter >= 3) {
                // tried 3 time to calculate route and failed skipping the room and putting it on the last
                // shifiting all the rooms to the right
                for(int j = i + 1; j < roomsIDs.size() - 1; j++) {
                    std::string p = roomsIDs[j];
                    roomsIDs[j] = roomsIDs[j + 1];
                    roomsIDs[j + 1] = p;
                }
            }
            // failed to calculate mission randomly changing place to try again

            // then reducing i by 1 and recalculate
            i = i-1;
            counter += 1;
            continue;
        }
        counter = 0;
        // lock the mutex
        this->mutex.lock();
        this->currentPlan.push(mission);
        // unlock the mutex
        this->mutex.unlock();
    }

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
    this->isInPlan = true;
    // copying the queue
    // lock
    this->mutex.lock();
    queue<Mission*> tempQueue = this->currentPlan;
    this->currentPlan = queue<Mission*>();
    this->mutex.unlock();
    while(tempQueue.size() > 0) {
        // get the next mission
        Mission* mission = tempQueue.front();
        // delete the mission from the queue
        tempQueue.pop();
        // do the mission
        mission->doMission();
        // delete the mission
        delete mission;
    }
    this->isInPlan = false;
    return 0;
}

void RobotPlanner::initRobot() {
    this->robotWrapper->initRobot();
}

bool RobotPlanner::isRobotOnline() {
    return this->robotWrapper->isOnline();
}

RobotWrapper *RobotPlanner::getRobotWrapper() {
    return this->robotWrapper;
}

void RobotPlanner::setPlanFromString(const string &plan) {
    // setting a given plan from a string
    // the first number of the string is the current robot room.

    // splitting the string by spaces
    std::vector<std::string> rooms;
    std::string token;
    std::stringstream ss(plan);

    while (std::getline(ss, token, ' ')) {
        rooms.push_back(token);
    }

    // creating mission to navigate, the first navigation is to go out of the room
    planNavigationMission(rooms);
}

bool RobotPlanner::isRobotInPlan() {
    return this->isInPlan;
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
