//
// Created by omer on 5/5/23.
//

#include "RobotBehaviorFactory.h"

RobotBehaviorFactory::RobotBehaviorFactory(RobotWrapper *robot, std::pair<double, double> goalPoint) {
    this->robot = robot;
    this->goalPoint = goalPoint;
    this->startPoint = goalPoint;
}

RobotBehavior *RobotBehaviorFactory::classifyAndReturnBehavior() {

    return nullptr;
}
