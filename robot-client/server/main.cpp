//
// Created by omer on 5/31/23.
//
#include "WebSocketServer.h"

int main(int argc, char **argv) {
    if(argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
        std::cout << "please start again with the following information above!" << std::endl;
        return 1;
    }

    // server main program
    int port = strtol(argv[2], nullptr, 10);
    if(port < 1024 || port > 65535) {
        std::cerr << "Error: invalid port number" << std::endl;
        std::cerr << "make sure the port number is between 1024 to 65535" << std::endl;
        return 1;
    }

    WebSocketServer serverWs(argv[1],port);
    serverWs.start();

    // Wait for user input to stop the server
    std::cout << "Server started at " << argv[1] << ":" << port << std::endl;
    std::cout << "Press ENTER to stop the server..." << std::endl;
    std::cin.ignore();

    serverWs.stop();

}