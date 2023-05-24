//
// Created by omer on 5/17/23.
//

#include "RotationBehavior.h"

RotationBehavior::RotationBehavior(RobotWrapper *robot, std::pair<double, double> goalPoint) : RobotBehavior(robot,
                                                                                                             goalPoint) {

}

RotationBehavior::~RotationBehavior() {

}

void RotationBehavior::avoidObstacles(double forwardSpeed, double turnSpeed) {
    // TODO: implement this function
}

int RotationBehavior::execute() {
    // this function will rotation the robot Yaw to the goal point.
    // getting robot instance
    PlayerCc::PlayerClient &client = this->robot->getClient();
    // getting robot position
    PlayerCc::Position2dProxy &pos = this->robot->getPos();

    // getting robot current information
    client.Read();

    // turning the robot to the goal point
    double goalPointAngle = atan2(this->goalPoint.second - pos.GetYPos(), this->goalPoint.first - pos.GetXPos());
    double robotAngleDefault = pos.GetYaw();
    double robotAngle = robotAngleDefault;
    double angleDiff = goalPointAngle - robotAngle;
    double angleDiffAbs = std::abs(angleDiff);
    double rotationSpeed = this->robot->getTurnSpeed();


    while (angleDiffAbs > 0.2) {
        // Calculate the updated robot angle
        robotAngle = pos.GetYaw() + robotAngleDefault;
        angleDiff = goalPointAngle - robotAngle;
        angleDiffAbs = std::abs(angleDiff);
        // Adjust rotation speed based on the robot's current angle
        if (robotAngle < 0 && rotationSpeed > 0) {
            rotationSpeed = -rotationSpeed;
        } else if (robotAngle >= 0 && rotationSpeed < 0) {
            rotationSpeed = -rotationSpeed;
        }

        // Check if the angle is close to 180 degrees (within a small range)
        if (angleDiff > M_PI) {
            angleDiff -= 2 * M_PI; // Adjust the angle difference
        } else if (angleDiff < -M_PI) {
            angleDiff += 2 * M_PI; // Adjust the angle difference
        }

        // Determine the rotation direction based on the angle difference
        if (angleDiff > 0) {
            pos.SetSpeed(0, -rotationSpeed); // Rotate to the right
        } else {
            pos.SetSpeed(0, rotationSpeed); // Rotate to the left
        }

        // Read the updated robot information and wait for a short duration
        client.Read();
        usleep(100);
    }
    
    // Stop the robot before adjusting the rotation speed
    pos.SetSpeed(0, 0);

//    // Update rotation speed for more accurate rotation
//    rotationSpeed = rotationSpeed / 3;
//
//    while (angleDiff > 0.1) {
//        // Calculate the updated robot angle
//        robotAngle = pos.GetYaw() + robotAngleDefault;
//        angleDiff = std::abs(goalPointAngle - robotAngle);
//
//        // Adjust rotation speed based on the robot's current angle
//        if (robotAngle < 0 && rotationSpeed > 0) {
//            rotationSpeed = -rotationSpeed;
//        } else if (robotAngle >= 0 && rotationSpeed < 0) {
//            rotationSpeed = -rotationSpeed;
//        }
//
//        // Check which direction (left or right) the angle is closer to
//        if (angleDiff > M_PI) {
//            pos.SetSpeed(0, -rotationSpeed); // Rotate to the right
//        } else {
//            pos.SetSpeed(0, rotationSpeed); // Rotate to the left
//        }
//
//        // Read the updated robot information and wait for a short duration
//        client.Read();
//        usleep(30);
//    }

//    pos.SetSpeed(0, 0);

    return 0; // success
}