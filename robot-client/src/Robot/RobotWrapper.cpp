//
// Created by omer on 5/5/23.
//

#include "RobotWrapper.h"


RobotWrapper::RobotWrapper(PlayerCc::PlayerClient* robot, PlayerCc::Position2dProxy* positionProxy,
                           PlayerCc::RangerProxy* laserProxy, std::string ws) {
    this->robot = robot;
    this->positionProxy = positionProxy;
    this->laserProxy = laserProxy;
    this->robotTurnSpeed = 0.03;
    this->robotGroundSpeed = 0.1;
    this->isRobotOnline = true;
    this->ws = ws;
    this->port = robot->GetPort();
    this->ip = robot->GetHostname();
}

//RobotWrapper::RobotWrapper(std::string robotIp, int robotPort, int groundSpeed, int turnSpeed) {
//    this->initRobot(robotIp, robotPort);
//    this->robotGroundSpeed = groundSpeed;
//    this->robotTurnSpeed = turnSpeed;
//}

//RobotWrapper::RobotWrapper(PlayerCc::PlayerClient& robot, PlayerCc::Position2dProxy& positionProxy, PlayerCc::RangerProxy& laserProxy) :
//        robot(robot) , positionProxy(positionProxy) , laserProxy(laserProxy){
//    this->robotTurnSpeed = 0.03;
//    this->robotGroundSpeed = 0.04;
//}


RobotWrapper::~RobotWrapper() {
//    if (this->positionProxy != nullptr) {
//        delete this->positionProxy;
//        this->positionProxy = nullptr;  // Set the pointer to null after deleting.
//    }
//    if (this->laserProxy != nullptr) {
//        delete this->laserProxy;
//        this->laserProxy = nullptr;  // Set the pointer to null after deleting.
//    }
//    this->getClient().Disconnect();
}

//void RobotWrapper::setRobotPath(std::pair<double, double> path) {
//    this->robotCurrentPath = path;
//}

void RobotWrapper::setRobotSpeed(double speed) {
    this->robotGroundSpeed = speed;
}

void RobotWrapper::setRobotTurnSpeed(double speed) {
    this->robotTurnSpeed = speed;
}

PlayerCc::Position2dProxy* RobotWrapper::getPos() {
    return this->positionProxy;
}

PlayerCc::RangerProxy* RobotWrapper::getLaser() {
    return this->laserProxy;
}

PlayerCc::PlayerClient* RobotWrapper::getClient() {
    return this->robot;
}

void RobotWrapper::initRobot() {
    // starting the robot process
    if(this->ip.empty() || this->port == 0){
        std::cout << "RobotWrapper::initRobot() - Robot ip or port is empty" << std::endl;
        return;
    }
    if(this->robot != nullptr){
        std::cout << "RobotWrapper::initRobot() - Robot is already initialized" << std::endl;
        std::cout << "RobotWrapper::initRobot() - Robot client at := ip: " << this->ip << " port: " << this->port << std::endl;
        return;
    }
    try {
        this->robot = new PlayerCc::PlayerClient(this->ip, this->port);
        this->positionProxy = new PlayerCc::Position2dProxy(this->robot);
        this->laserProxy = new PlayerCc::RangerProxy(this->robot);
//        this->robot->SetDataMode(PLAYER_DATAMODE_PULL);
//        this->robot->SetReplaceRule(true, PLAYER_MSGTYPE_DATA, -1);
        this->isRobotOnline = true;
    } catch (PlayerCc::PlayerError &e) {
        std::cerr << e << std::endl;
        this->isRobotOnline = false;
    }
}

double RobotWrapper::getGroundSpeed() {
    return this->robotGroundSpeed;
}

double RobotWrapper::getTurnSpeed() {
    return this->robotTurnSpeed;
}

std::pair<double, double> RobotWrapper::getCurrentPosition() {
    this->update();
    return std::make_pair(this->positionProxy->GetXPos(), this->positionProxy->GetYPos());
}

void RobotWrapper::update() {
    // lock the robot mutex
    std::lock_guard<std::mutex> lock(this->robotMutex);
    try {
        while (this->robot->Peek()) {
            usleep(50);
            this->robot->Read();
        }
    } catch (PlayerCc::PlayerError &e) {
//        std::cerr << e << std::endl;
    }
}

bool RobotWrapper::isObstacleOnLeft() {
    // using the ranger proxy to check if there is an obstacle on the left
    // if there is an obstacle on the left, return true
    // else return false
    this->update();
    PlayerCc::RangerProxy& ranger = *this->getLaser();
    // Get the total number of range readings
    int numReadings = ranger.GetRangeCount();
    // Calculate the number of readings on the left side
    int numReadingsOnLeft = numReadings / 2;
    // Define a threshold value for obstacle detection
    double obstacleThreshold = 0.5; // Adjust this value as needed
    // Check for obstacles on the left side
    for (int i = 0; i < numReadingsOnLeft; i++) {
        double range = ranger[i];
        if (range < obstacleThreshold) {
            // An obstacle is detected on the left side
            return true;
        }
    }
    // No obstacles found on the left side
    return false;
}

bool RobotWrapper::isObstacleOnRight() {
    // using the rangerproxy to check if there is an obstacle on the right
    // if there is an obstacle on the right, return true
    // else return false
    this->update();
    PlayerCc::RangerProxy& ranger = *this->getLaser();
    // Get the total number of range readings
    int numReadings = ranger.GetRangeCount();
    // Calculate the number of readings on the left side
    int numReadingsOnLeft = numReadings / 2;
    // Define a threshold value for obstacle detection
    double obstacleThreshold = 0.5; // Adjust this value as needed
    // Check for obstacles on the right side
    for (int i = numReadingsOnLeft; i < numReadings; i++) {
        double range = ranger[i];
        if (range < obstacleThreshold) {
            // An obstacle is detected on the right side
            return true;
        }
    }
    // No obstacles found on the right side
    return false;
}

bool RobotWrapper::hasObstaclesOnSides() {
    // Get the total number of range readings
    this->update();
    PlayerCc::RangerProxy &ranger = *this->getLaser();
    int numReadings = ranger.GetRangeCount();
    // Define a threshold value for obstacle detection
    double obstacleThreshold = 0.5; // Adjust this value as needed
    // Check for obstacles on both sides
    for (int i = 0; i < numReadings; i++) {
        double range = ranger[i];
        if (range < obstacleThreshold) {
            // An obstacle is detected on either side
            std::cout << "obstacle detected on side" << std::endl;
            return true;
        }
    }
    // No obstacles found on either side
    return false;
}

bool RobotWrapper::isOnline() {
    return this->isRobotOnline;
}

void RobotWrapper::setSpeed(double speed, double turnSpeed) {
    std::lock_guard<std::mutex> lock(this->robotMutex);
    this->positionProxy->SetSpeed(speed, turnSpeed);
}

void RobotWrapper::setCurrentPath(std::vector<std::pair<double, double>>  path) {
    this->robotCurrentPath = path;
}

std::vector<std::pair<double, double>>  RobotWrapper::getRobotCurrentPath() {
    return this->robotCurrentPath;
}

RobotWrapper::RobotWrapper(std::string ip, int port, std::string ws) {
    this->port = port;
    this->ip = ip;
    this->ws = ws;
    this->robotTurnSpeed = 0.03;
    this->robotGroundSpeed = 0.1;
    this->isRobotOnline = false;
    this->robot = nullptr;
    this->positionProxy = nullptr;
    this->laserProxy = nullptr;
}
