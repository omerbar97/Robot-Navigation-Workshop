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
    LinearNavigation navigateStraightLine;
    RotateRobot rotateTowards;
    for (Point& point : this->path) {
        rotateTowards(this->robot, point);
        navigateStraightLine(this->robot, point, 0.06, 0.1);
    }
}

HallNavigateBehavior::~HallNavigateBehavior() {

}

bool HallNavigateBehavior::avoidObstacles(double &forwardSpeed, double &turnSpeed) {
    double avoidDistance = 0.3;
    double avoidTurnSpeed = 60;
    PlayerCc::RangerProxy& laser = *this->robot->getLaser();

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




