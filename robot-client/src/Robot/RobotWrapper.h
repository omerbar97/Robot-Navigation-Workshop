//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
#include <libplayerc++/playerc++.h>
#include <string>
#include <nlohmann/json.hpp>
#include <mutex>

class RobotWrapper {
private:

    // robot instance
    PlayerCc::PlayerClient& robot;
    // robot extensions
    PlayerCc::Position2dProxy& positionProxy;
    PlayerCc::RangerProxy& laserProxy;
    bool isRobotOnline;
    double robotGroundSpeed;
    double robotTurnSpeed;
    std::vector<std::pair<double, double>> robotCurrentPath;
    void initRobot(std::string robotIp, int robotPort);
    std::mutex robotMutex;

public:

//    RobotWrapper(std::string robotIp = "localhost", int robotPort = 6665, int groundSpeed = 0.5, int turnSpeed = 0.1);
    RobotWrapper(PlayerCc::PlayerClient& robot, PlayerCc::Position2dProxy& positionProxy, PlayerCc::RangerProxy& laserProxy, std::string ws);
    ~RobotWrapper();

    void setRobotPath(std::pair<double, double> path);
    void setRobotSpeed(double speed);
    void setRobotTurnSpeed(double speed);
    void setSpeed(double speed, double turnSpeed);
    void setCurrentPath(std::vector<std::pair<double, double>>  path);


    double getGroundSpeed();
    double getTurnSpeed();
    std::pair<double, double> getCurrentPosition();
    bool isObstacleOnLeft();
    bool isObstacleOnRight();
    bool hasObstaclesOnSides();
    std::vector<std::pair<double, double>>  getRobotCurrentPath();

    // getRobot Extensions
    PlayerCc::Position2dProxy& getPos();
    PlayerCc::RangerProxy& getLaser();
    PlayerCc::PlayerClient& getClient();

    void update();
    bool isOnline();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
