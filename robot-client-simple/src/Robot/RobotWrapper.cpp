//
// Created by omer on 5/5/23.
//

#include "RobotWrapper.h"



RobotWrapper::RobotWrapper(PlayerCc::PlayerClient* robot, PlayerCc::Position2dProxy* positionProxy,
                           PlayerCc::RangerProxy* laserProxy, std::string ws) {
    this->robot = robot;
    this->positionProxy = positionProxy;
    this->laserProxy = laserProxy;
    this->robotTurnSpeed = 0.03; // default
    this->robotGroundSpeed = 0.1; // default
    this->isRobotOnline = true;
    this->ws = std::move(ws);
    this->port = robot->GetPort();
    this->ip = robot->GetHostname();
    this->enableFastTravel = true;
    this->startingRobotDegree = 0;
}


RobotWrapper::~RobotWrapper() {
    if (this->positionProxy != nullptr) {
        delete this->positionProxy;
        this->positionProxy = nullptr;  // Set the pointer to null after deleting.
    }
    if (this->laserProxy != nullptr) {
        delete this->laserProxy;
        this->laserProxy = nullptr;  // Set the pointer to null after deleting.
    }
    if (this->robot != nullptr) {
        delete this->robot;
        this->robot = nullptr;  // Set the pointer to null after deleting.
    }
}



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
        this->positionProxy = new PlayerCc::Position2dProxy(this->robot, 0);
        this->laserProxy = new PlayerCc::RangerProxy(this->robot, 1);
        this->laserProxy->RequestConfigure();
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
        while (this->robot->Peek(0)) {
            usleep(50);
            this->robot->Read();
        }
    } catch (PlayerCc::PlayerError &e) {
    }
}



bool RobotWrapper::isOnline() {
    return this->isRobotOnline;
}

void RobotWrapper::setSpeed(double speed, double turnSpeed) {
    std::lock_guard<std::mutex> lock(this->robotMutex);
    this->positionProxy->SetSpeed(speed, turnSpeed);
}


RobotWrapper::RobotWrapper(std::string ip, int port, std::string ws) {
    this->port = port;
    this->ip = std::move(ip);
    this->ws = std::move(ws);
    this->robotTurnSpeed = 0.03;
    this->robotGroundSpeed = 0.1;
    this->isRobotOnline = false;
    this->robot = nullptr;
    this->positionProxy = nullptr;
    this->laserProxy = nullptr;
    this->enableFastTravel = true;
    this->startingRobotDegree = 0;
}

double RobotWrapper::getYaw() {
    this->update();
    return this->positionProxy->GetYaw();
}

void RobotWrapper::setFastTravel(bool flag) {
    this->enableFastTravel = flag;
}

bool RobotWrapper::isFastTravelEnable() {
    return this->enableFastTravel;
}

void RobotWrapper::setStartingDegree(int degree) {
    this->startingRobotDegree = degree;
}

void RobotWrapper::setOnline(bool flag) {
    this->isRobotOnline = flag;
}
