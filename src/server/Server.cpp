//
// Created by omer on 5/25/23.
//

#include "Server.h"

Server::Server(std::string ip, int port) {
    this->ip = ip;
    this->listenPort = port;
    this->clientSocket = -1;
    this->serverSocket = -1;
}

Server::~Server() {

}

bool Server::init() {
    if ((this->serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        return false;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(listenPort);
    memset(serverAddress.sin_zero, '\0', sizeof(serverAddress.sin_zero));

    if (bind(this->serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Socket binding failed");
        return false;
    }

    if (listen(this->serverSocket, 5) == -1) {
        perror("Socket listening failed");
        return false;
    }

    std::cout << "Server started on port " << this->listenPort << std::endl;
    return true;
}


bool Server::acceptConnection() {
    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);

    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize)) == -1) {
        perror("Accepting connection failed");
        return false;
    }
    std::cout << "Accepted client connection" << std::endl;
    return true;
}

bool Server::recv() {
    // receiving data from socket
    char buffer[BUFFER_SIZE];
    if (clientSocket == -1) {
        std::cerr << "No client connected" << std::endl;
        return false;
    }
    if (::recv(clientSocket, &buffer, BUFFER_SIZE, MSG_PEEK) == -1) {
        perror("Receiving data failed");
        return false;
    } else {
        std::cout << "Received: " << buffer << std::endl;
        return true;
    }
}

bool Server::send(std::string data) {
    // sending data through socket
    if (clientSocket == -1) {
        std::cerr << "No client connected" << std::endl;
        return false;
    }
    if (::send(clientSocket, data.c_str(), data.size(), 0) == -1) {
        perror("Sending response failed");
        return false;
    }
    return true;
}
