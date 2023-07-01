//
// Created by omer on 5/5/23.
//

#include "RobotPlanner.h"


RobotPlanner::RobotPlanner(const string &roomConfigPath, RobotWrapper *robotWrapper, MapGenerator *map) {
    this->robotWrapper = robotWrapper;
    this->roomsContainer = new RoomsContainer(roomConfigPath);
    this->map = map;
    this->isInPlan = false;
    this->chronoTime = new ChronoTime();
    this->robotTimeoutThread == nullptr;
}

RobotPlanner::~RobotPlanner() {
    // deleting the rooms container
    delete (this->roomsContainer);
    this->robotWrapper->setOnline(false);
    if(this->robotTimeoutThread != nullptr) {
        this->robotTimeoutThread->join();
    }
    delete (this->map);
    delete (this->chronoTime);
    delete (this->robotWrapper);
}

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
        std::cout << RED << "the current robot location must be a valid room (the first room you enter)." << RESET_COLOR
                  << endl;
        return;
    }

    // assumes that the robot starts inside a room
    R2R *r2r;
    std::vector<string> rooms = removeDuplicates(roomsIDs);
    if (robotWrapper->isFastTravelEnable()) {
        // recalculating the rooms by sales man problem
        rooms = salesManProblem(rooms, this->robotWrapper->getCurrentPosition());
    }

    // shifting the rooms one to left
    auto prev = rooms[0];
    for (int j = 1; j <= rooms.size(); j++) {
        if (j != rooms.size()) {
            auto r = rooms[j];
            rooms[j] = prev;
            prev = r;
        } else {
            rooms.push_back(prev);
            break;
        }
    }
    rooms[0] = to_string(currentLocation->getRoomId());

    std::cout << BMAG << "creating path: ";
    for (int j = 0; j < rooms.size(); j++) {
        if (j != rooms.size() - 1) {
            std::cout << rooms[j] << "->";
        } else {
            std::cout << rooms[j];
        }
    }
    std::cout << RESET_COLOR << std::endl;


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
            r2r = new R2R(currentRoom, nextRoom, this->robotWrapper,
                          new RRTStarAlgorithm(), this->map, true);
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
                std::cout << YEL << "moving room id: " << nextRoom->getRoomId() << " to the end of the navigation list"
                          << COLOR_RESET << std::endl;
                for (; j < rooms.size() - 1; j++) {
                    std::string p = rooms[j];
                    rooms[j] = rooms[j + 1];
                    rooms[j + 1] = p;
                }
            }
        }
        //add the path to the vector
        std::vector<Point> points;

        auto *timeCalculation = new CalculateTime(this->chronoTime);
        auto *inform = new Inform(this->chronoTime, nextRoom);
        // lock the mutex
        this->missionLock.lock();
        this->currentPlan.push(timeCalculation);
        this->currentPlan.push(r2r);
        this->currentPlan.push(inform);
        // unlock the mutex
        this->missionLock.unlock();

    }
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

    this->robotLock.lock();
    while (tempQueue.size() > 0) {
        // get the next mission
        Mission *mission = tempQueue.front();
        // delete the mission from the queue
        tempQueue.pop();
        // do the mission
        int err;
        try {
            err = mission->doMission();
        } catch (std::exception &e) {
            // printing the room id that failed
            std::cout << "while doing a mission failed in room_id: " << e.what();
            finishGracefully(tempQueue);
            this->isInPlan = false;
            delete mission;
            this->robotLock.unlock();
            return -1;
        }
        // delete the mission
        if (err == -2) {
            std::cerr << RED << "mission failed: robot couldn't exit the room it is in." << std::endl;
            std::cerr << "maybe the current room you've entered is not the room it's currently in." << RESET_COLOR <<std::endl;
            finishGracefully(tempQueue);
            this->isInPlan = false;
            delete mission;
            this->robotLock.unlock();
            return -1;
        }
        delete mission;
    }
    this->isInPlan = false;
    this->robotLock.unlock();
    return 0;
}

void RobotPlanner::finishGracefully(queue<Mission *>& queue) {
    while(!queue.empty()) {
        Mission *mission = queue.front();
        queue.pop();
        delete mission;
    }
}

void RobotPlanner::initRobot() {
    this->robotWrapper->initRobot();
    this->robotTimeoutThread = new std::thread(&RobotPlanner::robotTimeout, this);
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
    std::cout << BGRN << "creating optimized path on: " << RESET_COLOR;
    for (auto s: roomsIDs) {
        std::cout << GRN << s << " , ";
    }
    std::cout << RESET_COLOR << std::endl;
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
    for (int i = 0; i < roomsIDs.size() - 1; i++) {
        // calculating the linear distances from all the rooms
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

        if (distances.size() == 0) {
            break;
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
        currentLocation = minRoom.room->getCenterPoint();

        // finding the room
        for (int k = 0; k < rooms.size(); k++) {
            if (minRoom.room->getRoomId() == rooms[k]->getRoomId()) {
                // removing the room from the rooms list
                rooms.erase(rooms.begin() + k);
                break;
            }
        }
    }

    std::vector<std::string> stringsId;
    for (auto r: arranged) {
        stringsId.push_back(to_string(r->getRoomId()));
    }
    return stringsId;
}

std::vector<std::string> RobotPlanner::removeDuplicates(std::vector<std::string> &vec) {
    std::unordered_set<std::string> uniqueElements;
    std::vector<std::string> result;

    for (const auto &str: vec) {
        if (uniqueElements.insert(str).second) {
            result.push_back(str);
        }
    }

    return result;
}

ChronoTime *RobotPlanner::getChronoTime() const {
    return chronoTime;
}

void RobotPlanner::setChronoTime(ChronoTime *chronoTime) {
    RobotPlanner::chronoTime = chronoTime;
}

void RobotPlanner::robotTimeout() {
    // sending data to the robot every 8 sec to avoid timeout
    while (this->isRobotOnline()) {
        std::this_thread::sleep_for(std::chrono::seconds(8));
        this->robotWrapper->update();
    }

    // deleting the robotWrapper
    delete this->robotWrapper;
}

void RobotPlanner::setRobotWrapper(RobotWrapper *robot) {
    if(this->robotWrapper != nullptr) {
        delete(this->robotWrapper);
    }
    this->robotWrapper = robot;
}










