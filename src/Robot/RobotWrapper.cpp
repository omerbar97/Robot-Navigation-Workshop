//
// Created by omer on 5/5/23.
//

#include "RobotWrapper.h"

//RobotWrapper::RobotWrapper(std::string robotIp, int robotPort, int groundSpeed, int turnSpeed) {
//    this->initRobot(robotIp, robotPort);
//    this->robotGroundSpeed = groundSpeed;
//    this->robotTurnSpeed = turnSpeed;
//}

RobotWrapper::RobotWrapper(PlayerCc::PlayerClient& robot, PlayerCc::Position2dProxy& positionProxy, PlayerCc::RangerProxy& laserProxy) :
            robot(robot) , positionProxy(positionProxy) , laserProxy(laserProxy){
    this->robotTurnSpeed = 0.03;
    this->robotGroundSpeed = 0.02;
}


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

void RobotWrapper::setRobotPath(std::pair<double, double> path) {
    this->robotCurrentPath = path;
}

void RobotWrapper::setRobotSpeed(double speed) {
    this->robotGroundSpeed = speed;
}

void RobotWrapper::setRobotTurnSpeed(double speed) {
    this->robotTurnSpeed = speed;
}

PlayerCc::Position2dProxy& RobotWrapper::getPos() {
    return this->positionProxy;
}

PlayerCc::RangerProxy& RobotWrapper::getLaser() {
    return this->laserProxy;
}

PlayerCc::PlayerClient& RobotWrapper::getClient() {
    return this->robot;
}

void RobotWrapper::initRobot(std::string robotIp, int robotPort) {
//    std::cout << "connection to robot: " << robotIp << ":" << robotPort << std::endl;
//    this->positionProxy = new PlayerCc::Position2dProxy(&this->robot, 0);
//    std::cout << "connection to robot position proxy" << std::endl;
//    this->laserProxy = new PlayerCc::LaserProxy(&this->robot, 0);
//    std::cout << "connection to robot laser proxy" << std::endl;
}

double RobotWrapper::getGroundSpeed() {
    return this->robotGroundSpeed;
}

double RobotWrapper::getTurnSpeed() {
    return this->robotTurnSpeed;
}

std::pair<double, double> RobotWrapper::getCurrentPosition() {
    this->update();
    return std::make_pair(this->positionProxy.GetXPos(), this->positionProxy.GetYPos());
}

void RobotWrapper::update() {
    try {
        while(this->robot.Peek()) {
            usleep(50);
            this->robot.Read();
        }
    } catch (PlayerCc::PlayerError & e) {
//        std::cerr << e << std::endl;
    }
}
