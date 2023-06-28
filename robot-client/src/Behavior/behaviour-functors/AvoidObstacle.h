//
// Created by omer on 6/26/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_AVOIDOBSTACLE_H
#define ROBOT_NAVIGATION_WORKSHOP_AVOIDOBSTACLE_H
#include "../../Robot/RobotWrapper.h"
#include "../RobotBehavior/RotationBehavior.h"
#include "LinearNavigation.h"
#include "RotateRobot.h"

using Point = std::pair<double, double>;

class AvoidObstacle {
private:
    Point transformToRealMapPoint(const Point& relativePoint, const Point& robotPosition, double robotOrientation);
    Point pointToTravel(int degree, double distance, std::pair<double, double> currentPos,  double yaw);
    Point getPointToTravel(int angleLeft, int angleRight, double leftDistance, double rightDistance, std::pair<double, double> currentPos, double sideC, double yaw);
    Point calculatePoint(double distance, double angle);
    double calculateTwoPointDistance(double sideA, double sideB, double angleC);
public:

    void operator()(RobotWrapper* robot, Point dest, double fSpeed, const double safeDistance, std::pair<int, int> angle, int depth);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_AVOIDOBSTACLE_H
