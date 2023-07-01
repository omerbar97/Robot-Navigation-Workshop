
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


using namespace PlayerCc;


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
    } else {
        // error
        std::cout << "Error: do not enter any arguments!" << std::endl;
        return 1;
    }
    return 0;
}