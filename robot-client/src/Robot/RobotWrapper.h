//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
#include <libplayerc++/playerc++.h>
#include <boost/bind/bind.hpp>
#include <string>
#include <nlohmann/json.hpp>
#include <mutex>
using namespace boost::placeholders;

class RobotWrapper {
private:

    // robot instance
    PlayerCc::PlayerClient* robot;
    PlayerCc::Position2dProxy* positionProxy;
    PlayerCc::RangerProxy* laserProxy;

    bool enableFastTravel;
    bool isRobotOnline;
    int port;
    std::string ip;
    double robotGroundSpeed;
    double robotTurnSpeed;
    std::string ws;
    std::vector<std::pair<double, double>> robotCurrentPath;
    std::mutex robotMutex;

public:

//    RobotWrapper(std::string robotIp = "localhost", int robotPort = 6665, int groundSpeed = 0.5, int turnSpeed = 0.1);
    RobotWrapper(PlayerCc::PlayerClient* robot, PlayerCc::Position2dProxy* positionProxy, PlayerCc::RangerProxy* laserProxy, std::string ws = nullptr);
    RobotWrapper(std::string ip, int port, std::string ws = nullptr);

    ~RobotWrapper();
    void setRobotPath(std::pair<double, double> path);

    void setRobotSpeed(double speed);
    void setRobotTurnSpeed(double speed);
    void setSpeed(double speed, double turnSpeed);
    void setCurrentPath(std::vector<std::pair<double, double>>  path);
    void initRobot();
    void setFastTravel(bool flag);
    double getYaw();


    double getGroundSpeed();
    double getTurnSpeed();
    std::pair<double, double> getCurrentPosition();
    bool isObstacleOnLeft();
    bool isObstacleOnRight();
    bool hasObstaclesOnSides();
    std::vector<std::pair<double, double>>  getRobotCurrentPath();

    // getRobot Extensions
    PlayerCc::Position2dProxy* getPos();
    PlayerCc::RangerProxy* getLaser();
    PlayerCc::PlayerClient* getClient();

    void update();
    bool isOnline();
    bool isFastTravelEnable();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
