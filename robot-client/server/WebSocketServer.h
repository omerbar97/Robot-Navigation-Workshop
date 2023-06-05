//
// Created by omer on 5/31/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_WEBSOCKETSERVER_H
#define ROBOT_NAVIGATION_WORKSHOP_WEBSOCKETSERVER_H
#include <iostream>
#include <fstream>
#include <string>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <unistd.h>
#include "Helper.h"
#include <sys/wait.h>

using json = nlohmann::json;
typedef websocketpp::server<websocketpp::config::asio> server;


class WebSocketServer {
private:
    server serverWs;
    std::string stageUrl;
    std::thread serverThread;
    std::string ip;
    int port;
    Helper helper;
    websocketpp::connection_hdl currentHdl;


public:

    WebSocketServer(std::string ip, int port);
    ~WebSocketServer();

    void start();
    void stop();

    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);
    void onOpen(websocketpp::connection_hdl hdl);
    void onClose(websocketpp::connection_hdl hdl);

    bool startStageProcess();
    bool startRobotControllerProcess();




};


#endif //ROBOT_NAVIGATION_WORKSHOP_WEBSOCKETSERVER_H