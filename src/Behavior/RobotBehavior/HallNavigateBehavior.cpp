//
// Created by omer on 5/8/23.
//

#include "HallNavigateBehavior.h"

HallNavigateBehavior::HallNavigateBehavior(RobotWrapper *robot, std::pair<double, double> goalPoint) : RobotBehavior(robot, goalPoint) {

}

int HallNavigateBehavior::execute() {
    // this function will navigate the robot in the hall environment, the robot will move forward until it will reach
    // the goal point.
    PlayerCc::Position2dProxy& pos = this->robot->getPos();
    // navigating the robot to the goal point
    // sense -> think -> act

    this->robot->update();
    double minDistance;
    double distance = sqrt(pow(this->goalPoint.first - pos.GetXPos(), 2) + pow(this->goalPoint.second - pos.GetYPos(), 2));
    minDistance = distance;
    double groundSpeed = this->robot->getGroundSpeed();
    double turnSpeed = 0;
//    pos.SetSpeed(this->robot->getGroundSpeed(), 0);
    while(distance > 0.1) {
        // sense
        this->robot->update();
        // think
        avoidObstacles(groundSpeed, turnSpeed);
        // act
        pos.SetSpeed(groundSpeed, turnSpeed);

        // calculating the distance
        distance = sqrt(pow(this->goalPoint.first - pos.GetXPos(), 2) + pow(this->goalPoint.second - pos.GetYPos(), 2));
//        if(minDistance - distance > 0.05) {
//            break;
//        }
        if(distance < minDistance) {
            minDistance = distance;
        }
    }

    pos.SetSpeed(0, 0);
}

HallNavigateBehavior::~HallNavigateBehavior() {

}

void HallNavigateBehavior::avoidObstacles(double &forwardSpeed, double &turnSpeed) {
    double avoidDistance = 0.3;
    double avoidTurnSpeed = 0.3;
    PlayerCc::RangerProxy& laser = this->robot->getLaser();
    if(laser[2] < avoidDistance)
    {
        std::cout << "avoiding obstacle turning right" << std::endl;
        forwardSpeed = 0;
        //turn right
        turnSpeed = (-1)*avoidTurnSpeed;
        return;
    }
    else if(laser[3] < avoidDistance)
    {
        std::cout << "avoiding obstacle turning left" << std::endl;
        forwardSpeed = 0;
        //turn left
        turnSpeed = avoidTurnSpeed;
        return;
    }
    else if( (laser[0] < avoidDistance) && \
               (laser[1] < avoidDistance))
    {
        //back off a little bit
        forwardSpeed = -0.2;
        turnSpeed = avoidTurnSpeed;
        return;
    }
    turnSpeed = 0;
    forwardSpeed = this->robot->getGroundSpeed();
    return; //do nothing
}


