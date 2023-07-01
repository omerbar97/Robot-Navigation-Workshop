//
// Created by omer on 6/9/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_WEBSOCKETCLIENT_H
#define ROBOT_NAVIGATION_WORKSHOP_WEBSOCKETCLIENT_H
#include "../Robot/RobotWrapper.h"
#include "../Robot/RobotPlanner.h"
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <nlohmann/json.hpp>
#include <regex>
#include <utility>


typedef websocketpp::client<websocketpp::config::asio_client> client;
/**
 * class to communicate with live data and sending it to the react using sockets.
 */
class WebSocketClient {
private:
    RobotWrapper* robot;
    std::vector<std::thread*> threads;
    RobotPlanner* planner;
    std::string ws;
    client wsClient;
    websocketpp::connection_hdl connection;

    void on_open(websocketpp::connection_hdl hdl);
    void on_close(websocketpp::connection_hdl hdl);
    void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);


public:

    WebSocketClient(RobotPlanner* robot, std::string ws);
    ~WebSocketClient();
    void run();
    void sendRobotPosition();
    void close();
    bool isOnline();


};


#endif //ROBOT_NAVIGATION_WORKSHOP_WEBSOCKETCLIENT_H
