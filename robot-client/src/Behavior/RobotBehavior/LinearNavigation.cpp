//
// Created by ofirhelerman on 6/11/23.
//

#include "LinearNavigation.h"


double LinearNavigation::
calcDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void LinearNavigation::
operator ()(RobotWrapper* robot, Point dest, double fSpeed, double tSpeed, const double minDistance) {

    // rotate robot using rotation behaviour to face the destination
    auto* rotationBehavior = new RotationBehavior(robot, dest);
    rotationBehavior->execute();

    // first, preparations for the straight line behaviour:
    PlayerCc::Position2dProxy pos = robot->getPos();
    robot->update();
    double distance = calcDistance(dest.first, dest.second,pos.GetXPos(), pos.GetYPos());
    pos.SetSpeed(fSpeed, tSpeed);

    // loop to bring robot to dest
    while ( distance > minDistance ) {

        // sense
        robot->update();

        // think
        // TODO: add here avoidObstacles() function

        // act
        distance = calcDistance(dest.first, dest.second,pos.GetXPos(), pos.GetYPos());
        usleep(10000);
    }

    // finished navigation
    pos.SetSpeed(0, 0);
    delete rotationBehavior;
}