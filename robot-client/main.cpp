
#include <libplayerc++/playerc++.h>
#include "src/Resources/MapGenerator.h"
#include "src/PathPlanning/Route.h"
#include "src/Resources/RoomsContainer.h"
#include "src/Robot/RobotWrapper.h"
#include "src/Behavior/RobotBehavior/RotationBehavior.h"
#include "src/Robot/RobotPlanner.h"
#include "src/Robot/RobotCLI.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <thread>

using namespace PlayerCc;

std::string getAbsolutePath(const std::string& relativePath) {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path absolutePath = currentPath / relativePath;
    return absolutePath.string();
}

bool runStageScript() {
    const std::string command = "gnome-terminal -- bash -c '../../general-use/run_stage.sh; exec bash'";
    int result = std::system(command.c_str());
    return result == 0;
}

void launch_robotCLI() {
    std::string mapGeneratorPath = getAbsolutePath("../maps/csMap.png");
    auto *map = new MapGenerator(mapGeneratorPath);

    PlayerClient client("localhost", 6665);
    Position2dProxy position(&client, 0);

    RangerProxy laser(&client, 1);
    auto* robotWrapper = new RobotWrapper(client, position, laser);
    std::string pathToRoomsConfig = getAbsolutePath("../configurations/room_coordinates.txt");
    auto* robotPlanner = new RobotPlanner(pathToRoomsConfig, robotWrapper, map);
    auto* robotCLI = new RobotCLI(robotPlanner);
    robotCLI->run();
}

void start_program() {
    std::thread stageThread(runStageScript);
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
    stageThread.join();
}

void unitTesting() {

    std::thread stageThread(runStageScript);
    std::cout << "Continue execution? [Y/n]: ";
    std::string answer;
    std::cin >> answer;
    std::cout << std::endl;
    if (answer == "Y" || answer == "y") {
        PlayerClient client("localhost", 6665);
        Position2dProxy position(&client, 0);
        RangerProxy laser(&client, 1);
        auto* robotWrapper = new RobotWrapper(client, position, laser);
        std::string pathToRoomsConfig = getAbsolutePath("../configurations/room_coordinates.txt");
        auto* roomsContainer = new RoomsContainer(pathToRoomsConfig);
        auto* enterRoom = new EnterRoomBehavior(robotWrapper, roomsContainer->getRoomById(1));
        enterRoom->execute();
//        auto* exitBehavior = new ExitRoomBehavior(robotWrapper, roomsContainer->getRoomById(1));
//        exitBehavior->execute();
    }

    std::cout << "waiting for stage to finish..." << std::endl;
    stageThread.join();
}


int main() {

//    testExit();
//    testNavigation();
//    unitTesting();
    start_program();
    return 0;
}