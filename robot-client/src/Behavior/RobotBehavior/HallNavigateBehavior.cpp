//
// Created by omer on 5/8/23.
//

#include "HallNavigateBehavior.h"
#include "../behaviour-functors/RotateRobot.h"

HallNavigateBehavior::HallNavigateBehavior(RobotWrapper *robot, vector<Point> &path) :
        RobotBehavior(robot, path.at(path.size() - 1)) {
    this->path = path;
}

//HallNavigateBehavior::HallNavigateBehavior(RobotWrapper *robot, vector<Point>& path) : RobotBehavior(robot, path) {

//}

int HallNavigateBehavior::execute() {
    // this function will navigate the robot in the hall environment, the robot will move forward until it will reach
    // the goal point.
    PlayerCc::Position2dProxy& pos = *this->robot->getPos();
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
    this->robot->setSpeed(groundSpeed, turnSpeed);
    while(distance > 0.1) {
//        if(!isTurning && latestTurn) {
//            // moving the robot a little bit forward, getting current position
//            // checking the laser scan if there is an obstacle in the side of the robot
//            // if there is an obstacle, we need to move the robot forward until the obstacle is not in the side of the robot
//            // if there is no obstacle, we need to rotate the robot to the goal point
//            // checking the laser scan
//
//            pos.SetSpeed(groundSpeed, 0);
//            while(this->robot->hasObstaclesOnSides()) {
//                // moving the robot forward
//                std::cout << "moving the robot forward" << std::endl;
//                usleep(10000);
//            }
//            latestTurn = false;
//            // need to redirect the robot to the goal point
//            // rotate the robot to the goal point
//            RotationBehavior rotationBehavior(this->robot, this->goalPoint);
//            rotationBehavior.execute();
//        }

        // sense
        this->robot->update();
        // think
//        isTurning = avoidObstacles(groundSpeed, turnSpeed);
//
//        // act
//        pos.SetSpeed(groundSpeed, turnSpeed);
//        if(isTurning && !latestTurn) {
//            latestTurn = true;
//            usleep(10000);
//        }
        // calculating the distance
        distance = sqrt(pow(this->goalPoint.first - pos.GetXPos(), 2) + pow(this->goalPoint.second - pos.GetYPos(), 2));
//        if(minDistance - distance > 0.05) {
//            break;
//        }
//        if(distance < minDistance) {
//            minDistance = distance;
//        }
        usleep(100);
    }

    this->robot->setSpeed(0, 0);
    return 0;
}

HallNavigateBehavior::~HallNavigateBehavior() {

    LinearNavigation navigateStraightLine;
    RotateRobot rotateTowards;
    for (Point& point : this->path) {
        // sense

        //think

        // act
        rotateTowards(this->robot, point);
        navigateStraightLine(this->robot, point, 0.06, 0.1);
    }
}

bool HallNavigateBehavior::avoidObstacles(double &forwardSpeed, double &turnSpeed) {
    double avoidDistance = 0.3;
    double avoidTurnSpeed = 60;
    PlayerCc::RangerProxy& laser = *this->robot->getLaser();
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




