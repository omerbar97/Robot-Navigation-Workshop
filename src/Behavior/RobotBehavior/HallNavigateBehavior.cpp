//
// Created by omer on 5/8/23.
//

#include "HallNavigateBehavior.h"

HallNavigateBehavior::HallNavigateBehavior(RobotWrapper *robot, std::pair<double, double> goalPoint) : RobotBehavior(robot, goalPoint) {

}

int HallNavigateBehavior::execute() {
    // this function will navigate the robot in the hall environment, the robot will move forward until it will reach
    // the goal point.

    // getting robot instance
    PlayerCc::PlayerClient &client = this->robot->getClient();
    // getting robot position
    PlayerCc::Position2dProxy *pos = this->robot->getPos();
    // getting robot laser
    PlayerCc::LaserProxy *laser = this->robot->getLaser();

    // getting robot current information
    client.Read();

    // navigating the robot to the goal point
    // sense -> think -> act

    double distance = sqrt(pow(this->goalPoint.first - pos->GetXPos(), 2) + pow(this->goalPoint.second - pos->GetYPos(), 2));
    while(distance < 0.2) {
        // sense
        client.Read();
        // if closest obstacle is less than 0.5m then stop
        if(laser->GetRange(0) < 0.5) {
            pos->SetSpeed(0, 0);
            return 1; // fail
        }

        pos->SetSpeed(this->robot->getGroundSpeed(), 0);
        sleep(10);

        client.Read();
        // calculating the distance
        distance = sqrt(pow(this->goalPoint.first - pos->GetXPos(), 2) + pow(this->goalPoint.second - pos->GetYPos(), 2));
    }
}