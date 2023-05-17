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
    PlayerCc::PlayerClient &client = this->robot->getClient();
    // getting robot position
    PlayerCc::Position2dProxy *pos = this->robot->getPos();

    // getting robot current information
    client.Read();

    // turning the robot to the goal point
    double goalPointAngle = atan2(this->goalPoint.second - pos->GetYPos(), this->goalPoint.first - pos->GetXPos());
    double robotAngle = pos->GetYaw();
    double angleDiff = goalPointAngle - robotAngle;
    while(angleDiff > 0.1) {
        pos->SetSpeed(0, this->robot->getTurnSpeed());
        client.Read();
        if(angleDiff < 0.1) {
            pos->SetSpeed(0, 0);
            break;
        }
        robotAngle = pos->GetYaw();
        angleDiff = goalPointAngle - robotAngle;
        sleep(100);
    }

    // more accurate slow speed
    int turnSpeed = this->robot->getTurnSpeed() / 2;
    while(angleDiff > 0.01) {
        pos->SetSpeed(0, turnSpeed);
        client.Read();
        if(angleDiff < 0.01) {
            pos->SetSpeed(0, 0);
            break;
        }
        robotAngle = pos->GetYaw();
        angleDiff = goalPointAngle - robotAngle;
        sleep(10);
    }

    return 0; // success
}