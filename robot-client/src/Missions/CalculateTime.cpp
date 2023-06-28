//
// Created by omer on 6/28/23.
//

#include "CalculateTime.h"

#include <utility>

CalculateTime::CalculateTime(std::vector<std::pair<double, double>> *path, double robotSpeed) {
    this->path = path;
    this->robotSpeed = robotSpeed;
    this->time = -1;
}

int CalculateTime::doMission() {
    // calculate the time to reach the point with the given speed

    // time X speed = road

    // calculating the linear distance between the path

    // distance = sqrt((x1 -x2)^2 + (y1-y2)^2)
    double distance = 0;
    for (int i = 1; i < path->size(); i++) {
        std::pair src = path->at(i - 1);
        std::pair dest = path->at(i);
        distance += sqrt(pow((src.first - dest.first), 2) + pow((src.second - dest.second), 2));
    }

    // calculating time in seconds

    // time X speed = road
    // time = road / speed

    time = distance / robotSpeed;
    // adding the time approximate for each professor to reach the robotic lab;
    time += 40; // seconds
    return 0;
}

double CalculateTime::getTime() {
    return this->time;
}

CalculateTime::~CalculateTime() {
    // deleting the path
    delete path;
}
