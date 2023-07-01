//
// Created by omer on 6/26/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_AVOIDOBSTACLE_H
#define ROBOT_NAVIGATION_WORKSHOP_AVOIDOBSTACLE_H
#include "../../Robot/RobotWrapper.h"
#include "LinearNavigation.h"
#include "RotateRobot.h"

using Point = std::pair<double, double>;

/**
 * This class is responsible for avoiding obstacles in the robot's path.
 * It uses the robot's sensors to detect obstacles and calculates a new path to the destination, while
 * avoiding the obstacles.
 */
class AvoidObstacle {
private:

    /**
     * function : transformToRealMapPoint
     * ----------------------------------
     * This function transforms a point from the robot's relative map to the real map.
     * @param relativePoint - the point in the robot's relative view of the space around it.
     * @param robotPosition - the robot's position in the real map.
     * @param robotOrientation - the robot's orientation in the real map.
     * @return the point in the real map.
     */
    Point transformToRealMapPoint(const Point& relativePoint, const Point& robotPosition, double robotOrientation);

    /**
     * function : pointToTravel
     * ------------------------
     * this function calculates the point the robot should travel to, in order to avoid the obstacle.
     * @param degree - where to locate the point to avoid the obstacle, in degrees.
     * @param distance - the distance from the robot to the obstacle.
     * @param currentPos - the robot's current position.
     * @param yaw - the robot's current orientation.
     * @return the point to travel to.
     */
    Point pointToTravel(int degree, double distance, std::pair<double, double> currentPos,  double yaw);

    /**
     * function : getPointToTravel
     * ---------------------------
     * @param angleLeft - the angle of the left point of the obstacle.
     * @param angleRight - the angle of the right point of the obstacle.
     * @param leftDistance - the distance from the robot to the left edge of the obstacle.
     * @param rightDistance - the distance from the robot to the right edge of the obstacle.
     * @param currentPos - the robot's current position.
     * @param sideC - the distance between the two sensors.
     * @param yaw - the robot's current orientation.
     * @return the point to travel to.
     */
    Point getPointToTravel(int angleLeft, int angleRight, double leftDistance, double rightDistance, std::pair<double, double> currentPos, double sideC, double yaw);

    /**
     * function : calculatePoint
     * -------------------------
     * calculates a point in the map, given a distance and an angle.
     * @param distance - the distance from the robot to the point.
     * @param angle - the angle of the point, in degrees, relative to 0 degrees of the map.
     * @return the point in the map.
     */
    Point calculatePoint(double distance, double angle);

    /**
     * function : calculateTwoPointDistance
     * ------------------------------------
     * calculates the distance between two points, given the length of the two sides and the angle between them.
     * @param sideA - the length of the first side.
     * @param sideB - the length of the second side.
     * @param angleC - the angle between the two sides.
     * @return the distance between the two points.
     */
    double calculateTwoPointDistance(double sideA, double sideB, double angleC);
public:

    /**
     * function : operator()
     * ----------------------
     * This function is the functor's operator. It is called when the functor is called.
     * @param robot - the robot's wrapper class.
     * @param dest - the robot's destination.
     * @param fSpeed - the robot's forward speed.
     * @param safeDistance - the distance from the robot to the obstacle, in which the robot will stop.
     * @param angle - the angle of the obstacle, in degrees.
     * @param depth - the depth of the recursion tree call.
     */
    void operator()(RobotWrapper* robot, Point dest, double fSpeed, const double safeDistance, std::pair<int, int> angle, int depth);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_AVOIDOBSTACLE_H
