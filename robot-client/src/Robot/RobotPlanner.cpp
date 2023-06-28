//
// Created by omer on 5/5/23.
//

#include "RobotPlanner.h"

RobotPlanner::RobotPlanner(const string &roomConfigPath, RobotWrapper *robotWrapper, MapGenerator *map) {
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
void RobotPlanner::planInformMission(const vector<string> &roomsIDs) {
    // currently, the function assumes that inform mission is only to move between rooms.

    // if inside a room -
    // if inside if the first room - then inform the person in the room
    // if inside any other room - then navigate regularly, but first exit the room

    // if in the hallway - navigate to the next room regularly


}


void RobotPlanner::planNavigationMission(vector<string> &roomsIDs) {
    // validation
    Room *currentLocation = this->roomsContainer->getRoomById(stoi(roomsIDs.at(0)));
    if (currentLocation == nullptr) {
        // the current location must be a valid room
        std::cout << RED << "the current location must be a valid room (the first room you enter)." << RESET_COLOR
                  << endl;
        return;
    }

    // first mission is to get out of the room, doing it in a different thread
    Mission *m = new R2Exit(currentLocation, this->robotWrapper);
    std::thread* exitRoomThread = new std::thread([m, ptr = this]() -> void {
        std::lock_guard<std::mutex> lock(ptr->robotLock);
        while(true) {
            try{
                ptr->isInPlan = true;
                m->doMission();
                break;
            } catch (std::exception &e) {
                std::cout << "error " << e.what();
            }
        }
        delete(m);
        ptr->isInPlan = false;
        ptr->cv.notify_all();
        std::cout << "finished!\n";
    });

    exitRoomThread->detach();

    // assumes that the robot starts inside a room
    Mission *mission;
    std::vector<string> rooms;
    if (robotWrapper->isFastTravelEnable()) {
        // recalculating the rooms by sales man problem
        rooms = salesManProblem(roomsIDs, this->robotWrapper->getCurrentPosition());
    } else {
        rooms = roomsIDs;
    }

    for (int i = 0; i < rooms.size() - 1; i++) {
        Room *currentRoom = this->roomsContainer->getRoomById(stoi(rooms.at(i)));
        Room *nextRoom = this->roomsContainer->getRoomById(stoi(rooms.at(i + 1)));
        while (nextRoom == nullptr) {
            // deleting the room
            std::cout << RED << "within the room list, room id: " << rooms.at(i + 1)
                      << " is not a valid room id (by the current configuration file), skipping the room" << RESET_COLOR
                      << endl;
            i++;
            if (i >= rooms.size() - 1) {
                // reached to the end
                return;
            }
            std::cout << YEL << "trying to calculate path from room id: " << currentRoom->getRoomId() << " to room id: "
                      << rooms.at(i + 1) << RESET_COLOR << endl;
            nextRoom = this->roomsContainer->getRoomById(stoi(rooms.at(i + 1)));
        }
        try {
            if (i == 0) {
                // the current room, exiting via a new thread
                mission = new R2R(currentRoom, nextRoom, this->robotWrapper,
                                  new RRTStarAlgorithm(), this->map, false);
            } else {
                // all the other room need to add exit behavior
                mission = new R2R(currentRoom, nextRoom, this->robotWrapper,
                                  new RRTStarAlgorithm(), this->map, true);
            }
        } catch (std::exception &e) {
            // tried 3 time to calculate route and failed skipping the room and putting it on the last
            // shifting all the rooms to the right
            int j = i + 1;
            if (j == rooms.size() - 1) {
                // cannot calculate path to the end room
                std::cout << RED << "the room id: " << nextRoom->getRoomId()
                          << " was at the end of the plan execution list and failed to create path from room id: "
                          << currentRoom->getRoomId() << " aborting mission!" << COLOR_RESET << std::endl;
            } else {
                std::cout << YEL << "moving room id: " << nextRoom->getRoomId() << " to the end the navigation list"
                          << COLOR_RESET << std::endl;
                for (; j < rooms.size() - 1; j++) {
                    std::string p = rooms[j];
                    rooms[j] = rooms[j + 1];
                    rooms[j + 1] = p;
                }
            }
        }
        // lock the mutex
        this->missionLock.lock();
        this->currentPlan.push(mission);
        // unlock the mutex
        this->missionLock.unlock();

//        if(!this->isInPlan) {
//            std::unique_lock<std::mutex> uniqueLock(this->robotLock);
//            cv.wait(uniqueLock);
//            // the thread finished the job, executing the already mission queue
//            exitRoomThread = new thread([ptr = this]() -> void {
//                ptr->executePlan();
//            });
//        }

    }
//    if(exitRoomThread->joinable()) {
//        // the thread didn't finished yet detaching it.
//        exitRoomThread->detach();
//    }
}

void RobotPlanner::plan(const MissionType &mission, vector<std::string> &parameters) {
    switch (mission) {
        case MissionType::NAVIGATION:
            planNavigationMission(parameters);
            break;
        case MissionType::INFORM:
            planInformMission(parameters);
            break;
        default:
            cout << "mission type not supported" << endl;
            return;
    }
}

/**
 * set the rooms of the robot
 * @param rooms - the rooms to set
 */
int RobotPlanner::executePlan() {
    this->isInPlan = true;
    // copying the queue
    // locking the mission queue
    this->missionLock.lock();
    queue<Mission *> tempQueue = this->currentPlan;
    this->currentPlan = queue<Mission *>();
    this->missionLock.unlock();
//    if(!this->robotLock.try_lock()) {
//        // cannot get lock
//        std::cout << YEL << "cannot receive robot-lock, waiting for the thread to finish executing the current robot plan" << RESET_COLOR << endl;
//    }
    this->robotLock.lock();
    while (tempQueue.size() > 0) {
        // get the next mission
        Mission *mission = tempQueue.front();
        // delete the mission from the queue
        tempQueue.pop();
        // do the mission
        try {
            mission->doMission();
        } catch (std::exception &e) {
            // printing the room id that failed
            std::cout << "error " << e.what();
        }
        // delete the mission
        delete mission;
    }
    this->isInPlan = false;
    this->robotLock.unlock();
    cv.notify_all();
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

std::vector<std::string> RobotPlanner::salesManProblem(const vector<string> &roomsIDs, Point currentLocation) {
    // re-arrange the rooms faster
    std::vector<Room *> rooms;
    std::vector<Room *> arranged;
    for (int i = 1; i < roomsIDs.size(); i++) {
        Room *rr = this->roomsContainer->getRoomById(stoi(roomsIDs[i]));
        if (rr == nullptr) {
            std::cout << YEL << "while trying to optimize the path, the algorithm encounter an invalid room id: "
                      << roomsIDs[i] << " creating an optimize path without it." << RESET_COLOR << endl;
        } else {
            rooms.push_back(this->roomsContainer->getRoomById(stoi(roomsIDs[i])));
        }
    }

    // all rooms now in the vector rooms

    // re arrange the rooms
    int size = roomsIDs.size();
    for (int i = 0; i < size - 1; i++) {
        // calculating the distances from all the rooms
        std::vector<arrangedRoom> distances;
        for (Room *r: rooms) {
            Point dest = r->getCenterPoint();
            double distance = sqrt(
                    pow((currentLocation.first - dest.first), 2) + pow((currentLocation.second - dest.second), 2));
            arrangedRoom tempRoom;
            tempRoom.distance = distance;
            tempRoom.room = r;
            distances.push_back(tempRoom);
        }

        // finding the minimum of that list
        arrangedRoom minRoom = distances[0];

        for (int j = 1; j < distances.size(); j++) {
            if (minRoom.distance > distances[j].distance) {
                minRoom = distances[j];
            }
        }

        // adding to the arranged
        arranged.push_back(minRoom.room);

        // finding the room
        for (int k = 0; k < rooms.size(); k++) {
            if (minRoom.room->getRoomId() == rooms[k]->getRoomId()) {
                // removing the room from the rooms list
                rooms.erase(rooms.begin() + k);
                break;
            }
        }
    }

    // std::vector
}



