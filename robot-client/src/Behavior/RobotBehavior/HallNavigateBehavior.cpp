//
// Created by omer on 5/8/23.
//

#include "HallNavigateBehavior.h"
#include "../behaviour-functors/RotateRobot.h"

HallNavigateBehavior::HallNavigateBehavior(RobotWrapper *robot, vector<Point> &path) :
        RobotBehavior(robot, path.at(path.size() - 1)) {
    this->path = path;
}


int HallNavigateBehavior::execute() {
    LinearNavigation navigateStraightLine;
    RotateRobot rotateTowards;
    // setting the robot sensitivity
    std::pair<int, int> angles;
    angles.first = 70;
    angles.second = 110;
    for (Point& point : this->path) {
        rotateTowards(this->robot, point);
        navigateStraightLine(this->robot, point, this->robot->getGroundSpeed(), 0.1, angles);
    }
}

HallNavigateBehavior::~HallNavigateBehavior() {

}




