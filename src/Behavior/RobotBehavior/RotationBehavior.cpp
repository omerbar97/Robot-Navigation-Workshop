//
// Created by omer on 5/17/23.
//

#include "RotationBehavior.h"

RotationBehavior::RotationBehavior(RobotWrapper *robot, std::pair<double, double> goalPoint) : RobotBehavior(robot,
                                                                                                             goalPoint) {

}

RotationBehavior::~RotationBehavior() {

}

void RotationBehavior::avoidObstacles(double &forwardSpeed, double &turnSpeed) {

}

int RotationBehavior::execute() {
    // this function will rotation the robot Yaw to the goal point.
    // getting robot instance
    PlayerCc::PlayerClient &client = this->robot->getClient();
    // getting robot position
    PlayerCc::Position2dProxy &pos = this->robot->getPos();

    // getting robot current information
    this->robot->update();

    // turning the robot to the goal point
    double desiredRelativeAngle = atan2(this->goalPoint.second - pos.GetYPos(), this->goalPoint.first - pos.GetXPos());
    double currentOrientation;
    double rotationSpeed = this->robot->getTurnSpeed();
    double angleDiff;

    while (true) {
        // getting robot current information
        this->robot->update();
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

    return 0; // success
}