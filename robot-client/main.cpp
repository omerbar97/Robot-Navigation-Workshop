
#include <libplayerc++/playerc++.h>
#include "src/Resources/MapGenerator.h"
#include "src/Navigate/Navigation.h"
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


void testExitBehav() {

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
        auto* exitBehavior = new ExitRoomBehavior(robotWrapper, roomsContainer->getRoomById(1));
        exitBehavior->execute();
    }

    std::cout << "waiting for stage to finish..." << std::endl;
    stageThread.join();
}

int main() {


    testExitBehav();
//    start_program();
    return 0;
}

//int main(int argc, char **argv) {
//    MapGenerator *map = new MapGenerator(
//            "/home/ofirhelerman/CS-BIU/YearB/RoboticsSeminar/src-clion-robotics/robot-client/maps/csMap.png");
//
//    RoomsContainer roomHandler(
//            "/home/ofirhelerman/CS-BIU/YearB/RoboticsSeminar/src-clion-robotics/robot-client/configurations/room_coordinates.txt", {2,1});
//    PlayerCc::PlayerClient client("localhost", 6665);
//    PlayerCc::Position2dProxy position(&client, 0);
//    PlayerCc::RangerProxy laser(&client, 1);
////    client.Read();
//
//    std::list<playerc_device_info_t> t = client.GetDeviceList();
//
//
//    for(auto i : t) {
//        std::cout << "drivername: " << i.drivername << std::endl;
//        std::cout << "index " << i.addr.index << std::endl;
//    }
//    std::cout << position.GetYaw() << std::endl;
//
//    RobotWrapper* robotWrapper = new RobotWrapper(client, position, laser);
//
//    // create path
//    Route *route = new Route(new RRTStarAlgorithm(), map);
//
//    std::pair<double, double> start = robotWrapper->getCurrentPosition();
//    route->setStartingPoint(start);
//    route->setGoalPoint(roomHandler.getRooms()[0].getCenterPoint());
////    printf("getGoalPoint -%\n", roomHandler.getRooms()[0].getCenterPoint());
//    std::cout << "getGoalPoint" << roomHandler.getRooms()[0].getCenterPoint().first << " , " << roomHandler.getRooms()[0].getCenterPoint().second << std::endl;
//
//    route->createPath();
//    std::vector<std::pair<double, double> > path = route->getLatestPath();
//    for(int i = 1; i < path.size(); i++) {
//        //rotation to the point
//        std::cout << "rotation to the point: " << path[i].first << " , " << path[i].second << std::endl;
//        RotationBehavior rotationBehavior(robotWrapper, path[i]);
//        rotationBehavior.execute();
//        std::cout << "navigate to point: " << path[i].first << " , " << path[i].second << std::endl;
//        HallNavigateBehavior hallNavigateBehavior(robotWrapper, path[i]);
//        hallNavigateBehavior.execute();
//
//    }
//
//
//   // MapGenerator *map1 = new MapGenerator(
//   //         "/home/shilopadael/CLionProjects/Robotica/Robot-Navigation-Workshop/robot-client/maps/csMap.png");
//
//    //Route *route1 = new Route(new RRTStarAlgorithm(), map1);
////    Route *route2 = new Route(new RRTStarAlgorithm(), map);
//    //route->setMapGenerator(map);
//    start = robotWrapper->getCurrentPosition();
//    route->setStartingPoint(start);
//    route->setGoalPoint(roomHandler.getRooms()[1].getCenterPoint());
//    std::cout << "getGoalPoint" << roomHandler.getRooms()[1].getCenterPoint().first << " , " << roomHandler.getRooms()[1].getCenterPoint().second << std::endl;
//
//
//
//    route->createPath();
//    path = route->getLatestPath();
//    for(int i = 1 ; i < path.size() ; i++) {
//        //rotation to the point
//        std::cout << "rotation to the point: " << path[i].first << " , " << path[i].second << std::endl;
//        RotationBehavior rotationBehavior(robotWrapper, path[i]);
//        rotationBehavior.execute();
//        std::cout << "navigate to point: " << path[i].first << " , " << path[i].second << std::endl;
//        HallNavigateBehavior hallNavigateBehavior(robotWrapper, path[i]);
//        hallNavigateBehavior.execute();
//
//    }
//
//    start = robotWrapper->getCurrentPosition();
//    route->setStartingPoint(start);
//    route->setGoalPoint(roomHandler.getRooms()[0].getCenterPoint());
//    std::cout << "getGoalPoint" << roomHandler.getRooms()[0].getCenterPoint().first << " , " << roomHandler.getRooms()[1].getCenterPoint().second << std::endl;
//
//
//
//    route->createPath();
//    path = route->getLatestPath();
//    for(int i = 1 ; i < path.size() ; i++) {
//        //rotation to the point
//        std::cout << "rotation to the point: " << path[i].first << " , " << path[i].second << std::endl;
//        RotationBehavior rotationBehavior(robotWrapper, path[i]);
//        rotationBehavior.execute();
//        std::cout << "navigate to point: " << path[i].first << " , " << path[i].second << std::endl;
//        HallNavigateBehavior hallNavigateBehavior(robotWrapper, path[i]);
//        hallNavigateBehavior.execute();
//
//    }
//
//    start = robotWrapper->getCurrentPosition();
//    route->setStartingPoint(start);
//    route->setGoalPoint(roomHandler.getRooms()[1].getCenterPoint());
//    std::cout << "getGoalPoint" << roomHandler.getRooms()[1].getCenterPoint().first << " , " << roomHandler.getRooms()[1].getCenterPoint().second << std::endl;
//
//
//
//    route->createPath();
//    path = route->getLatestPath();
//    for(int i = 1 ; i < path.size() ; i++) {
//        //rotation to the point
//        std::cout << "rotation to the point: " << path[i].first << " , " << path[i].second << std::endl;
//        RotationBehavior rotationBehavior(robotWrapper, path[i]);
//        rotationBehavior.execute();
//        std::cout << "navigate to point: " << path[i].first << " , " << path[i].second << std::endl;
//        HallNavigateBehavior hallNavigateBehavior(robotWrapper, path[i]);
//        hallNavigateBehavior.execute();
//
//    }
//
//
////    Server server("localhost", 8080);
////    std::thread* serverThread;
////    if(server.init()) {
////        serverThread = new std::thread(&Server::acceptConnection, &server);
////        serverThread->detach();
////        while(true) {
////            std::string n;
////            std::cin >> n;
////            server.send(n);
////            server.recv();
////        }
////    }
//
////    VoiceMessageBehavior voiceMessageBehavior("ofir ve shilo ya-manyakym", "kamika");
////    voiceMessageBehavior.execute();

//    return 0;
//
//}




//void drawBlock(cv::Mat &map, int x, int y, int blockSize) {
//    for (int i = x; i < x + blockSize; i++) {
//        for (int j = y; j < y + blockSize; j++) {
//            map.at<uchar>(j, i) = 255; // Set to a higher value (255) for better visibility
//        }
//    }
//}
//
//void printToFile(std::string filename, cv::Mat &map) {
//    std::ofstream file;
//    file.open(filename);
//    for (int i = 0; i < map.rows; i++) {
//        for (int j = 0; j < map.cols; j++) {
//            file << (int) map.at<uchar>(i, j) << " ";
//        }
//        file << std::endl;
//    }
//    file.close();
//}
