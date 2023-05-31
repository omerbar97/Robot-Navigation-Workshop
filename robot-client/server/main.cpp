//
// Created by omer on 5/31/23.
//
#include "WebSocketServer.h"

int main(int argc, char **argv) {
    // server main program
    WebSocketServer serverWs("localhost",9000);
    serverWs.start();

    // Wait for user input to stop the server
    std::cout << "Press ENTER to stop the server..." << std::endl;
    std::cin.ignore();

    serverWs.stop();

}