//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
#include <libplayerc++/playerc++.h>
#include <string>

class RobotWrapper {
private:

    // robot instance
    PlayerCc::PlayerClient& robot;

    // robot extensions
    PlayerCc::Position2dProxy& positionProxy;
//    PlayerCc::LaserProxy* laserProxy;

    double robotGroundSpeed;
    double robotTurnSpeed;

    std::pair<double, double> robotCurrentPath;

    void initRobot(std::string robotIp, int robotPort);

public:

//    RobotWrapper(std::string robotIp = "localhost", int robotPort = 6665, int groundSpeed = 0.5, int turnSpeed = 0.1);
    RobotWrapper(PlayerCc::PlayerClient& robot, PlayerCc::Position2dProxy& positionProxy);
    ~RobotWrapper();

    void setRobotPath(std::pair<double, double> path);
    void setRobotSpeed(double speed);
    void setRobotTurnSpeed(double speed);

    double getGroundSpeed();
    double getTurnSpeed();
    std::pair<double, double> getCurrentPosition();

    // getRobot Extensions
    PlayerCc::Position2dProxy& getPos();
    PlayerCc::LaserProxy* getLaser();
    PlayerCc::PlayerClient& getClient();

    void update();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
