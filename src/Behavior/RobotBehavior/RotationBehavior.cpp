//
// Created by omer on 5/17/23.
//

#include "RotationBehavior.h"

RotationBehavior::RotationBehavior(RobotWrapper *robot, std::pair<double, double> goalPoint) : RobotBehavior(robot,
                                                                                                             goalPoint) {

}

RotationBehavior::~RotationBehavior() {

}

int RotationBehavior::execute() {
    // this function will rotation the robot Yaw to the goal point.
    // getting robot instance
    PlayerCc::PlayerClient& client = this->robot->getClient();
    // getting robot position
    PlayerCc::Position2dProxy& pos = this->robot->getPos();

    // getting robot current information
    client.Read();

    // turning the robot to the goal point
    double goalPointAngle = atan2(this->goalPoint.second - pos.GetYPos(), this->goalPoint.first - pos.GetXPos());
    double robotAngle = pos.GetYaw();
    double angleDiff = std::abs(goalPointAngle - robotAngle);
    double rotationSpeed = this->robot->getTurnSpeed();

    std::cout <<"robot angle " << robotAngle << "\n";

    if (robotAngle < 0) {
        rotationSpeed = -rotationSpeed;
    }
    while(angleDiff > 0.1) {
        if (robotAngle < 0) {
            rotationSpeed = -rotationSpeed;
        }
        // checking which angle is closer left or right
        pos.SetSpeed(0, rotationSpeed);
        client.Read();
        if(angleDiff < 0.1) {
            pos.SetSpeed(0, 0);
            break;
        }
        robotAngle = pos.GetYaw();
        angleDiff = std::abs(goalPointAngle - robotAngle);
        usleep(100);
    }
    pos.SetSpeed(0, 0);
    rotationSpeed = rotationSpeed / 2;
    // more accurate slow speed
    while(angleDiff > 0.03) {
        if (robotAngle < 0) {
            rotationSpeed = -rotationSpeed;
        }
//        std::cout <<"robot angle " << robotAngle << "\n";
        // checking which angle is closer left or right
        pos.SetSpeed(0, rotationSpeed);
        client.Read();
        if(angleDiff < 0.03) {
            pos.SetSpeed(0, 0);
            break;
        }
        robotAngle = pos.GetYaw();
        angleDiff = std::abs(goalPointAngle - robotAngle);
        usleep(30);
    }

    return 0; // success
}