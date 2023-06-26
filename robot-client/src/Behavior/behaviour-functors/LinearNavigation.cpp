//
// Created by ofirhelerman on 6/11/23.
//

#include "LinearNavigation.h"


void LinearNavigation::
operator ()(RobotWrapper* robot, Point dest, double fSpeed, const double minDistance ) {

    PlayerCc::Position2dProxy& pos = *robot->getPos();
    PlayerCc::RangerProxy& laser = *robot->getLaser();
    robot->update();
    auto currentPosition = robot->getCurrentPosition();
    double distance = sqrt(pow(dest.first - currentPosition.first, 2) + pow(dest.second - currentPosition.second, 2));
    double groundSpeed = robot->getGroundSpeed();
    double turnSpeed = 0, lastDistance = distance;
    robot->setSpeed(groundSpeed, turnSpeed);
    // debug
    AvoidObstacle avoidObstacle;
    std::pair<int, int> angles;
    angles.first = 70;
    angles.second = 110;
    std::cout << "minDistance: " << minDistance << std::endl;
    while(distance > minDistance) {

        // debug
//        std::cout << "distance: " << distance << std::endl;
//        int i = laser.GetRangeCount();
//        for(int j = 0; j < i; j++) {
//            std::cout << "laser[" <<  j << "]: " << laser[j] << std::endl;
//
//        }
//        std::cout << "distance to point " << distance << std::endl;
        // sense
        robot->update();

        // think
        // TODO: implement obstacle avoidance
        avoidObstacle(robot, dest, groundSpeed, 0.5, angles);


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

    pos.SetSpeed(0, 0);
}