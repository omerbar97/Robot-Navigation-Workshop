//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
#include <libplayerc++/playerc++.h>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <string>
#include <nlohmann/json.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class RobotWrapper {
private:

    // robot instance
    PlayerCc::PlayerClient& robot;
    // robot extensions
    PlayerCc::Position2dProxy& positionProxy;
    PlayerCc::RangerProxy& laserProxy;
    client* clientWs;
    websocketpp::connection_hdl hdlServer;
    bool isRobotOnline;
    double robotGroundSpeed;
    double robotTurnSpeed;
    std::pair<double, double> robotCurrentPath;
    void initRobot(std::string robotIp, int robotPort);

public:

//    RobotWrapper(std::string robotIp = "localhost", int robotPort = 6665, int groundSpeed = 0.5, int turnSpeed = 0.1);
    RobotWrapper(PlayerCc::PlayerClient& robot, PlayerCc::Position2dProxy& positionProxy, PlayerCc::RangerProxy& laserProxy, std::string ws);
    ~RobotWrapper();

    void setRobotPath(std::pair<double, double> path);
    void setRobotSpeed(double speed);
    void setRobotTurnSpeed(double speed);


    double getGroundSpeed();
    double getTurnSpeed();
    client* getWsClient();
    std::pair<double, double> getCurrentPosition();
    bool isObstacleOnLeft();
    bool isObstacleOnRight();
    bool hasObstaclesOnSides();

    // getRobot Extensions
    PlayerCc::Position2dProxy& getPos();
    PlayerCc::RangerProxy& getLaser();
    PlayerCc::PlayerClient& getClient();

    void update();
    void sendRobotPosition();
    void startClient(client::connection_ptr con);


};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
