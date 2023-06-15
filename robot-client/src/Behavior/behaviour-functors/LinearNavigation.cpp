//
// Created by ofirhelerman on 6/11/23.
//

#include "LinearNavigation.h"


void LinearNavigation::
operator ()(RobotWrapper* robot, Point dest, double fSpeed, const double minDistance ) {

    PlayerCc::Position2dProxy& pos = robot->getPos();
    robot->update();

    double distance = sqrt(pow(dest.first - pos.GetXPos(), 2) + pow(dest.second - pos.GetYPos(), 2));
    double groundSpeed = robot->getGroundSpeed();
    double turnSpeed = 0;
    pos.SetSpeed(groundSpeed, turnSpeed);

    while(distance > minDistance) {

        // sense
        robot->update();

        // think
        // TODO: implement obstacle avoidance

        // act
        pos.SetSpeed(fSpeed, turnSpeed);

        // calculating the distance
        distance = sqrt(pow(dest.first - pos.GetXPos(), 2) + pow(dest.second - pos.GetYPos(), 2));
        usleep(10);
    }

    pos.SetSpeed(0, 0);
}