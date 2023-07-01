//
// Created by omer on 6/26/23.
//

#include "AvoidObstacle.h"

void AvoidObstacle::operator()(RobotWrapper *robot, Point dest, double fSpeed, const double safeDistance,
                               std::pair<int, int> angle, int depth) {

    PlayerCc::RangerProxy &ranger = *robot->getLaser();
    int obstacleAngle;
    LinearNavigation linear;
    bool flag = false;
    int firstAngle = -1, secondAngle = -1;
    double minnuminDistacne = 10000;
    for (int j = angle.first; j <= angle.second; j++) {
        // checking the heading of the robot if there is obstacle
        if (ranger[j] < safeDistance) {
            // avoid
            if(minnuminDistacne > ranger[j]){
                minnuminDistacne = ranger[j];
            }
            if (firstAngle == -1) {
                firstAngle = j;
            }
            secondAngle = j;
        }
    }

    if (firstAngle == -1 && secondAngle == -1) {
        // exit
        return;
    }

    if(minnuminDistacne < 0.3) {
        robot->setSpeed(-robot->getGroundSpeed() / 2, 0);
        usleep(700000);
        return;
    }

    // stopping the robot
    robot->setSpeed(0, 0);

    // detected
    int f1 = std::abs(firstAngle - angle.first);
    int f2 = std::abs(secondAngle - angle.second);

    if (f1 > f2 && f1 != 0) {
        // scanning right
        int temp = -1;
        bool isFirst = false;
        double sideC;
        double distanceToSecondObstacle;
        for (int i = angle.second; i < 180; i++) {
            if (ranger[i] < safeDistance) {
                // obstacle
                temp = i;
                distanceToSecondObstacle = ranger[i];
                break;
            }
        }
        if(temp != -1) {
            sideC = calculateTwoPointDistance(ranger[secondAngle], ranger[temp], temp - secondAngle);

            // checking if the robot can pass through that distance
            if(sideC > 0.4) {
                // robot can pass
                auto point = getPointToTravel(secondAngle, temp, ranger[secondAngle], ranger[temp], robot->getCurrentPosition(), sideC, robot->getYaw());

                // navigate to the point, rotate
                RotateRobot rotate;
                rotate(robot, point);

                // travel to point
                linear(robot, point, robot->getGroundSpeed() / 2, 0.1, angle, ++depth);
                rotate(robot, dest);
                return;
            }
            else {
                // flag that indicates if the robot need to try the right side
                flag = true;
//                std::cout << "trying left side\n";
            }
        } else {
            // rotating the robot 30 degree
            auto point = pointToTravel(-20, ranger[secondAngle], robot->getCurrentPosition(), robot->getYaw());
            RotateRobot rotate;
            rotate(robot, point);

            // travel to point
            linear(robot, point, robot->getGroundSpeed() / 2, 0.1, angle, ++depth);
            rotate(robot, dest);
            return;


        }
    } if((f2 > f1 && f2 != 0) || flag) {
        // scanning left
        int temp = -1;
        double sideC;
        double distanceToSecondObstacle;
        for (int i = angle.first; i >= 0; i--) {
            if (ranger[i] < safeDistance) {
                // obstacle
                temp = i;
                distanceToSecondObstacle = ranger[i];
                break;
            }
        }
        if(temp != -1) {
            sideC = calculateTwoPointDistance(ranger[firstAngle], ranger[temp], firstAngle - temp);

            // checking if the robot can pass through that distance
            if(sideC > 0.4) {
                // robot can pass
                auto point = getPointToTravel(temp, firstAngle, ranger[temp], ranger[firstAngle], robot->getCurrentPosition(), sideC, robot
                ->getYaw());


                // navigate to the point, rotate
                RotateRobot rotate;
                rotate(robot, point);

                // travel to point
                linear(robot, point, robot->getGroundSpeed() / 2, 0.1, angle, ++depth);
                rotate(robot, dest);
                return;

            } else {
                auto point = pointToTravel(10, ranger[firstAngle], robot->getCurrentPosition(), robot->getYaw());
                RotateRobot rotate;

                rotate(robot, point);

                // travel to point
                linear(robot, point, robot->getGroundSpeed() / 2, 0.1, angle, ++depth);
                rotate(robot, dest);
                return;

            }
        } else {
            // turning left with 30 degree angle
            auto point = pointToTravel(20, ranger[firstAngle], robot->getCurrentPosition(), robot->getYaw());
            RotateRobot rotate;

            rotate(robot, point);

            // travel to point
            linear(robot, point, robot->getGroundSpeed() / 2, 0.1, angle, ++depth);
            rotate(robot, dest);
            return;

        }
    }
    else {
        auto point = pointToTravel(-10, ranger[firstAngle], robot->getCurrentPosition(), robot->getYaw());
        RotateRobot rotate;

        rotate(robot, point);

        // travel to point
        linear(robot, point, robot->getGroundSpeed() / 2, 0.1, angle, 0);
        rotate(robot, dest);

    }
}

double AvoidObstacle::calculateTwoPointDistance(double sideA, double sideB, double angleC) {
    // Convert angle from degrees to radians
    double angleRadians = angleC * M_PI / 180.0;

    // Calculate the missing side length using the sine rule
    double missingSide = (sideA * sin(angleRadians)) / sin(M_PI - angleRadians - asin(sideA * sin(angleRadians) / sideB));

    return missingSide;
}

Point AvoidObstacle::calculatePoint(double distance, double angle) {
    // Convert angle from degrees to radians
    double angleRadians = angle * M_PI / 180.0;

    // Calculate the coordinates of the point
    double x = distance * cos(angleRadians);
    double y = distance * sin(angleRadians);

    // Create a Point struct to hold the coordinates
    Point point;
    point.first = x;
    point.second = y;

    return point;
}

Point AvoidObstacle::getPointToTravel(int angleLeft, int angleRight, double leftDistance, double rightDistance,
                                      std::pair<double, double> currentPos, double sideC, double yaw) {
    auto pointLeft = calculatePoint(leftDistance, angleLeft);
    auto pointRight = calculatePoint(rightDistance, angleRight);


    double ratio = 0.7 / sideC;

    Point travelPoint;
    travelPoint.first = pointLeft.first + ratio * (pointRight.first - pointLeft.first);
    travelPoint.second = pointLeft.second + ratio * (pointRight.second - pointLeft.second);

    travelPoint = transformToRealMapPoint(travelPoint,currentPos,yaw);

    return travelPoint;

}

Point AvoidObstacle::pointToTravel(int degree, double distance, std::pair<double, double> currentPos, double yaw) {
    auto point = calculatePoint(distance, degree);
    double angleRadians = degree * M_PI / 180.0;

    double missingDistance = distance * tan(angleRadians);

    point.first += missingDistance;

    point = transformToRealMapPoint(point,currentPos, yaw);
    return point;
}

Point AvoidObstacle::transformToRealMapPoint(const Point &relativePoint, const Point &robotPosition,
                                             double robotOrientation) {
    double cosTheta = std::cos(robotOrientation);
    double sinTheta = std::sin(robotOrientation);

    Point transformedPoint;
    transformedPoint.first = (relativePoint.first * cosTheta) - (relativePoint.second * sinTheta) + robotPosition.first;
    transformedPoint.second = (relativePoint.first * sinTheta) + (relativePoint.second * cosTheta) + robotPosition.second;

    return transformedPoint;
}

