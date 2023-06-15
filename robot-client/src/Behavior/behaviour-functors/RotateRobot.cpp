//
// Created by ofirhelerman on 6/15/23.
//

#include "RotateRobot.h"

void RotateRobot::operator()(RobotWrapper *robot, const Point& goalPoint) {
    // getting robot position
    PlayerCc::Position2dProxy &pos = robot->getPos();

    // getting robot current information
    robot->update();

    // turning the robot to the goal point
    double desiredRelativeAngle = atan2(goalPoint.second - pos.GetYPos(), goalPoint.first - pos.GetXPos());
    double currentOrientation;
    double rotationSpeed = robot->getTurnSpeed();
    double angleDiff;

    while (true) {
        // getting robot current information
        robot->update();
        currentOrientation = pos.GetYaw();
        angleDiff = desiredRelativeAngle - currentOrientation;

        // Handle angle wrapping
        if (angleDiff > M_PI) {
            angleDiff -= 2 * M_PI;
        } else if (angleDiff < -M_PI) {
            angleDiff += 2 * M_PI;
        }
        if (fabs(angleDiff) < 0.01) {
            break;
        }

        // Determine rotation direction based on the sign of angleDiff
        if (angleDiff > 0) {
            pos.SetSpeed(0, rotationSpeed);  // Rotate right
        } else if(angleDiff <= 0){
            pos.SetSpeed(0, -rotationSpeed);  // Rotate left
        }

        usleep(100);
    }

    pos.SetSpeed(0, 0);
}