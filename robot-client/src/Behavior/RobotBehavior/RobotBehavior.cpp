//
// Created by omer on 5/17/23.
//

#include "RobotBehavior.h"

RobotBehavior::RobotBehavior(RobotWrapper *robot, std::pair<double, double> goalPoint) {
    this->robot = robot;
    this->goalPoint = goalPoint;
}
