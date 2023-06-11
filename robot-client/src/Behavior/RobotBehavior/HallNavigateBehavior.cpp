//
// Created by omer on 5/8/23.
//

#include "HallNavigateBehavior.h"

HallNavigateBehavior::HallNavigateBehavior(RobotWrapper *robot, Point goalPoint) : RobotBehavior(robot, goalPoint) {

}

HallNavigateBehavior::HallNavigateBehavior(RobotWrapper *robot, vector<Point> path) : RobotBehavior(robot, path) {

}

int HallNavigateBehavior::execute() {
    // this function will navigate the robot in the hall environment, the robot will move forward until it will reach
    // the goal point.
    PlayerCc::Position2dProxy& pos = this->robot->getPos();
    // navigating the robot to the goal point


    this->robot->update();
    double minDistance;
    double distance = sqrt(pow(this->goalPoint.first - pos.GetXPos(), 2) + pow(this->goalPoint.second - pos.GetYPos(), 2));
    minDistance = distance;
    double groundSpeed = this->robot->getGroundSpeed();
    bool isTurning = false;
    bool latestTurn = false;
    double turnSpeed = 0;
    pos.SetSpeed(groundSpeed, turnSpeed);

    while(distance > 0.1) {

        // sense
        this->robot->update();
        // think
//        isTurning = avoidObstacles(groundSpeed, turnSpeed);
        std::cout<<"isTurning: "<<isTurning<<std::endl;

        // act
        pos.SetSpeed(groundSpeed, turnSpeed);
        if(isTurning && !latestTurn) {
            latestTurn = true;
            usleep(10000);
        }
        // calculating the distance
        distance = sqrt(pow(this->goalPoint.first - pos.GetXPos(), 2) + pow(this->goalPoint.second - pos.GetYPos(), 2));
        usleep(10);
    }

    pos.SetSpeed(0, 0);
}


HallNavigateBehavior::~HallNavigateBehavior() {

}

bool HallNavigateBehavior::avoidObstacles(double &forwardSpeed, double &turnSpeed) {
    double avoidDistance = 0.3;
    double avoidTurnSpeed = 60;
    PlayerCc::RangerProxy& laser = this->robot->getLaser();
    std::cout << "laser[0]: " << laser[0] << std::endl;
    std::cout << "laser[1]: " << laser[1] << std::endl;
    std::cout << "laser[2]: " << laser[2] << std::endl;
    std::cout << "laser[3]: " << laser[3] << std::endl;

    // Check if obstacle on the right
    if (laser[2] < avoidDistance) {
        std::cout << "Avoiding obstacle by turning right" << std::endl;
        forwardSpeed = 0;
        turnSpeed = -avoidTurnSpeed;
        return true;
    }
        // Check if obstacle on the left
    else if (laser[3] < avoidDistance) {
        std::cout << "Avoiding obstacle by turning left" << std::endl;
        forwardSpeed = 0;
        turnSpeed = avoidTurnSpeed;
        return true;
    }
        // Check if obstacles ahead and on the sides
    else if (laser[0] < avoidDistance && laser[1] < avoidDistance) {
        std::cout << "Avoiding obstacle by backing off and turning" << std::endl;
        forwardSpeed = -0.2;
        turnSpeed = avoidTurnSpeed;
        return true;
    }

    // No obstacles, proceed with normal navigation
//    turnSpeed = 0;
//    forwardSpeed = this->robot->getGroundSpeed();
    return false;
}


