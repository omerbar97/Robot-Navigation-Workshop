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
    bool isTurning = false;
    bool latestTurn = false;
    double turnSpeed = 0;
    pos.SetSpeed(groundSpeed, turnSpeed);
    while(distance > 0.1) {
        if(!isTurning && latestTurn) {
            // moving the robot a little bit forward, getting current position
            // checking the laser scan if there is an obstacle in the side of the robot
            // if there is an obstacle, we need to move the robot forward until the obstacle is not in the side of the robot
            // if there is no obstacle, we need to rotate the robot to the goal point
            // checking the laser scan

            pos.SetSpeed(groundSpeed, 0);
            while(this->robot->hasObstaclesOnSides()) {
                // moving the robot forward
                std::cout << "moving the robot forward" << std::endl;
                usleep(10000);
            }
            latestTurn = false;
            // need to redirect the robot to the goal point
            // rotate the robot to the goal point
            RotationBehavior rotationBehavior(this->robot, this->goalPoint);
            rotationBehavior.execute();
        }

        // sense
        this->robot->update();
        // think
//        isTurning = avoidObstacles(groundSpeed, turnSpeed);

        // act
        pos.SetSpeed(groundSpeed, turnSpeed);
        if(isTurning && !latestTurn) {
            latestTurn = true;
            usleep(10000);
        }
        // calculating the distance
        distance = sqrt(pow(this->goalPoint.first - pos.GetXPos(), 2) + pow(this->goalPoint.second - pos.GetYPos(), 2));
//        if(minDistance - distance > 0.05) {
//            break;
//        }
//        if(distance < minDistance) {
//            minDistance = distance;
//        }
        printf("groudSpeed: %f, turnSpeed: %f, distance: %f\n", groundSpeed, turnSpeed, distance);
        usleep(10);
    }

    pos.SetSpeed(0, 0);
}

HallNavigateBehavior::~HallNavigateBehavior() {

}

bool HallNavigateBehavior::avoidObstacles(double &forwardSpeed, double &turnSpeed) {
    double avoidDistance = 0.3;
    double avoidTurnSpeed = 0.3;
    PlayerCc::RangerProxy& laser = this->robot->getLaser();
    if(laser[2] < avoidDistance)
    {
        std::cout << "avoiding obstacle turning right" << std::endl;
        forwardSpeed = 0;
        //turn right
        turnSpeed = (-1)*avoidTurnSpeed;
        return true;
    }
    else if(laser[3] < avoidDistance)
    {
        std::cout << "avoiding obstacle turning left" << std::endl;
        forwardSpeed = 0;
        //turn left
        turnSpeed = avoidTurnSpeed;
        return true;
    }
    else if( (laser[0] < avoidDistance) && \
               (laser[1] < avoidDistance))
    {
        //back off a little bit
        forwardSpeed = -0.2;
        turnSpeed = avoidTurnSpeed;
        return true;
    }
    turnSpeed = 0;
    forwardSpeed = this->robot->getGroundSpeed();
    return false; //do nothing
}


