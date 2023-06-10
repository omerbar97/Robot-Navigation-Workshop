//
// Created by omer on 6/9/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_WEBSOCKETCLIENT_H
#define ROBOT_NAVIGATION_WORKSHOP_WEBSOCKETCLIENT_H
#include "../Robot/RobotWrapper.h"
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <nlohmann/json.hpp>


typedef websocketpp::client<websocketpp::config::asio_client> client;
class WebSocketClient {
private:
    RobotWrapper* robot;
    std::string ws;
    client wsClient;
    websocketpp::connection_hdl connection;

    void on_open(websocketpp::connection_hdl hdl);
    void on_close(websocketpp::connection_hdl hdl);
    void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);
    void on_fail(websocketpp::connection_hdl hdl);
    void on_pong(websocketpp::connection_hdl hdl, std::string msg);
    void on_interrupt(websocketpp::connection_hdl hdl);

public:
    WebSocketClient(RobotWrapper* robot, std::string ws);

    ~WebSocketClient();

    void run();

    void sendRobotPosition();
    void sendRobotPath();

    void close();

    void update();

    bool isOnline();

    void setRobot(RobotWrapper* robot);

    void setWs(std::string ws);

    RobotWrapper* getRobot();

    std::string getWs();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_WEBSOCKETCLIENT_H
