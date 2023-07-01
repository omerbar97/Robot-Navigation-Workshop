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
    std::string requestIp;
    bool isStageOnline;
    bool isRobotOnline;
    pid_t stagePid;
    pid_t robotPid;
    int port;
    Helper helper;
    websocketpp::connection_hdl currentHdl;


public:

    WebSocketServer(std::string ip, int port);
    ~WebSocketServer();

    /**
     * starting the websocket server
     */
    void start();

    /**
     * stopping the websocket server.
     */
    void stop();

    /**
     * the callback function when an message is received.
     * @param hdl - hdl connection format about the sender
     * @param msg - the content
     */
    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);

    /**
     * the callback function when a new connection is connected.
     * @param hdl - hdl connection format about the sender
     */
    void onOpen(websocketpp::connection_hdl hdl);

    /**
     * the callback function when a connection is off.
     * @param hdl
     */
    void onClose(websocketpp::connection_hdl hdl);

    /**
     * starting the stage process
     * @param hdl
     * @return
     */
    bool startStageProcess(websocketpp::connection_hdl hdl);

    /**
     * starting the robot-navigation control program in a different process
     * @param hdl
     * @return
     */
    bool startRobotControllerProcess(websocketpp::connection_hdl hdl);

};


#endif //ROBOT_NAVIGATION_WORKSHOP_WEBSOCKETSERVER_H
