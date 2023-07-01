//
// Created by ofirhelerman on 6/11/23.
//

#include "LinearNavigation.h"


void LinearNavigation::
operator ()(RobotWrapper* robot, Point dest, double fSpeed, const double minDistance, std::pair<int, int> angles, int depth) {
//    std::cout << "depth: " << depth << "\n";
    if(depth >= 10) {
        // to many attempts
        // backing off a little bit
        robot->setSpeed(-robot->getGroundSpeed() / 2, 0);
        usleep(700000);
        robot->setSpeed(0, 0);
        throw std::exception();
    }

    PlayerCc::Position2dProxy& pos = *robot->getPos();
    PlayerCc::RangerProxy& laser = *robot->getLaser();
    robot->update();
    auto currentPosition = robot->getCurrentPosition();
    double distance = sqrt(pow(dest.first - currentPosition.first, 2) + pow(dest.second - currentPosition.second, 2));
    double groundSpeed = 0.05;
    double turnSpeed = 0, lastDistance = distance;
    robot->setSpeed(groundSpeed, turnSpeed);
    // debug
    AvoidObstacle avoidObstacle;
    while(distance > minDistance) {


        // sense
        robot->update();

        // think
        avoidObstacle(robot, dest, groundSpeed, 0.5, angles, depth);


        // act
        robot->setSpeed(fSpeed, turnSpeed);

        // calculating the distance
        currentPosition = robot->getCurrentPosition();
        distance = sqrt(pow(dest.first - currentPosition.first, 2) + pow(dest.second - currentPosition.second, 2));
        if(lastDistance < distance) {
            break;
        } else {
            lastDistance = distance;
        }
        usleep(10);
    }

//    std::cout << "Reached to point: " << dest.first << " , " << dest.second << " \n";
    pos.SetSpeed(0, 0);
}