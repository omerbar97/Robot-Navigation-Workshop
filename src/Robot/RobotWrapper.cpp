//
// Created by omer on 5/5/23.
//

#include "RobotWrapper.h"

RobotWrapper::RobotWrapper(std::string robotIp, int robotPort, int groundSpeed, int turnSpeed) :
         robot(robotIp, robotPort) {
    this->initRobot(robotIp, robotPort);
    this->robotGroundSpeed = groundSpeed;
    this->robotTurnSpeed = turnSpeed;
}

RobotWrapper::~RobotWrapper() {
    if(this->positionProxy != nullptr) {
        delete this->positionProxy;
    }
    if(this->laserProxy != nullptr) {
        delete this->laserProxy;
    }
}

void RobotWrapper::setRobotPath(std::pair<double, double> path) {
    this->robotCurrentPath = path;
}

void RobotWrapper::setRobotSpeed(int speed) {
    this->robotGroundSpeed = speed;
}

void RobotWrapper::setRobotTurnSpeed(int speed) {
    this->robotTurnSpeed = speed;
}

PlayerCc::Position2dProxy* RobotWrapper::getPos() {
    return this->positionProxy;
}

PlayerCc::LaserProxy* RobotWrapper::getLaser() {
    return this->laserProxy;
}

PlayerCc::PlayerClient &RobotWrapper::getClient() {
    return this->robot;
}

void RobotWrapper::initRobot(std::string robotIp, int robotPort) {
    std::cout << "connection to robot: " << robotIp << ":" << robotPort << std::endl;
    this->positionProxy = new PlayerCc::Position2dProxy(&this->robot, 0);
    std::cout << "connection to robot position proxy" << std::endl;
    this->laserProxy = new PlayerCc::LaserProxy(&this->robot, 0);
    std::cout << "connection to robot laser proxy" << std::endl;
}