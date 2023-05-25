//
// Created by omer on 5/25/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_SERVER_H
#define ROBOT_NAVIGATION_WORKSHOP_SERVER_H
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>

#define BUFFER_SIZE 1024
/**
 * handle the connection between a node.js server and the robot interface
 */
class Server {
private:
    int listenPort;
    int serverSocket;
    int clientSocket;
    std::string ip;
    struct sockaddr_in serverAddress;
//    std::string messageToWrite;

public:
    Server(std::string ip, int port);
    ~Server();

    /**
     * connect to the server
     */
    bool init();
    bool acceptConnection();


//    void setMessageToWrite(std::string message);
    bool send(std::string data);
    bool recv();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_SERVER_H
