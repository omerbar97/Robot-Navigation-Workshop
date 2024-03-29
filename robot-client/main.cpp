
#include <libplayerc++/playerc++.h>
#include "src/Resources/MapGenerator.h"
#include "src/Resources/RoomsContainer.h"
#include "src/Robot/RobotWrapper.h"
#include <thread>
#include "src/Robot/RobotPlanner.h"
#include "src/Robot/RobotCLI.h"
#include <string>
#include <filesystem>
#include <iostream>
#include "src/Client/WebSocketClient.h"


using namespace PlayerCc;

/**
 * different thread to start the WebSocketClient that is connected to the react live data.
 * @param planner - RobotPlanner
 * @param ws - string
 */
void startWs(RobotPlanner *planner, std::string ws) {
    auto *client = new WebSocketClient(planner, ws);

    // setting another thread for the position sending
    std::thread wsThread(&WebSocketClient::sendRobotPosition, client);

    // running the thread to handle the client requests

    client->run();
    wsThread.join();
}

// signal keyboard ctrl+c handler
void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
    std::cout << "closing program..." << std::endl;
    exit(0);
}

std::string getAbsolutePath(const std::string &relativePath) {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path absolutePath = currentPath / relativePath;
    return absolutePath.string();
}

RobotPlanner *createRobotPlanner(std::string ip, int port, std::string ws) {
    PlayerClient *client = new PlayerClient(std::move(ip), port);
    Position2dProxy *position = new Position2dProxy(client, 0);
    RangerProxy *laser = new RangerProxy(client, 1);
    RobotWrapper *wrapper = new RobotWrapper(client, position, laser, ws);
    laser->RequestConfigure();
    std::string mapGeneratorPath = getAbsolutePath("../maps/fromServer.png");
    auto *map = new MapGenerator("../maps/fromServer.png");
    std::string pathToRoomsConfig = "../configurations/room_coordinates.txt";
    auto *robotPlanner = new RobotPlanner(pathToRoomsConfig, wrapper, map);
    return robotPlanner;
}

void launch_robotCLI() {
    std::string mapGeneratorPath = getAbsolutePath("../maps/fromServer.png");
    auto *map = new MapGenerator("../maps/fromServer.png");
    std::string path = "localhost";

    auto *robotWrapper = new RobotWrapper(path, 6665, path);
    std::string pathToRoomsConfig = getAbsolutePath("../configurations/room_coordinates.txt");
    auto *robotPlanner = new RobotPlanner("../configurations/room_coordinates.txt", robotWrapper, map);
    auto *robotCLI = new RobotCLI(robotPlanner);
    robotCLI->run();
    delete (robotCLI);
}

void start_program() {
    std::cout << "Launch robot's CLI? [Y/n]: ";
    std::string answer;
    std::cin >> answer;
    std::cout << std::endl;
    if (answer == "Y" || answer == "y") {
        std::cout << "Launching robot's CLI..." << std::endl << std::endl;
        // Clear the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.clear();
        launch_robotCLI();
    } else {
        std::cout << "Exiting robot's CLI launcher..." << std::endl;
    }
    std::cout << "waiting for stage to finish..." << std::endl;
}


int main(int argc, char *argv[]) {
    if (argc == 1) {
        // running the cli
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);
        start_program();
        return 0;
    } else if (argc != 4) {
        // error
        std::cout << "Error: invalid number of arguments" << std::endl;
        return 1;
    }

    // running the robot client from the server
    std::string ip = argv[1];
    int port= atoi(argv[2]);
    std::string ws = argv[3];
    RobotPlanner *robotPlanner = createRobotPlanner(ip, port, ws);

    // creating thread to send location
    std::thread *thread;
    thread = new std::thread(startWs, robotPlanner, ws);

    // handle mission from the server

    thread->join();
    delete(thread);
    return 0;
}