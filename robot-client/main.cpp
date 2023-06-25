
#include <libplayerc++/playerc++.h>
#include "src/Resources/MapGenerator.h"
#include "src/PathPlanning/Route.h"
#include "src/Resources/RoomsContainer.h"
#include "src/Robot/RobotWrapper.h"
#include "src/Behavior/RobotBehavior/RotationBehavior.h"
#include <thread>
#include "src/Robot/RobotPlanner.h"
#include "src/Robot/RobotCLI.h"
#include <string>
#include <filesystem>
#include <iostream>
#include "src/Client/WebSocketClient.h"


void startWs(RobotWrapper *robotWrapper, std::string ws) {
    WebSocketClient* client = new WebSocketClient(robotWrapper, ws);

    // setting another thread for the position sending
    std::thread wsThread(&WebSocketClient::sendRobotPosition, client);

    client->run();
    wsThread.join();
}

//
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
//
//using namespace PlayerCc;
//
//int main(int argc, char **argv) {
//    if (argc != 4) {
//        // error
//        std::cout << "Error: invalid number of arguments" << std::endl;
//        return 1;
//    }
//
//    MapGenerator *map = new MapGenerator(
//            "/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/robot-client/maps/fromServer.png");
//
//    RoomsHandler roomHandler(
//            "/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/robot-client/configures/room_coordinates.txt",
//            {15});
//    int port = strtol(argv[2], nullptr, 10);
//    std::cout << "port: " << port << std::endl;
//    std::cout << "ip: " << argv[1] << std::endl;
////    if(port < 0 || port > 65535) {
////        std::cout << "Error: invalid port number" << std::endl;
////        return 1;
////    }
//    std::string ip = argv[1];
//    PlayerCc::PlayerClient client(ip, port);
//    PlayerCc::Position2dProxy position(&client, 0);
//    PlayerCc::RangerProxy laser(&client, 1);
//
//    std::list<playerc_device_info_t> t = client.GetDeviceList();
//
//
//    std::cout << position.GetYaw() << std::endl;
//
//    RobotWrapper *robotWrapper = new RobotWrapper(client, position, laser, "ws://localhost:8081");
//    std::string ws = argv[3];
//
//    // Run a member function of robotWrapper in a separate thread
//    std::thread* thread;
//    thread = new std::thread(startWs, robotWrapper, ws);
//
//
//    // create path
//    Route *route = new Route(new RRTStarAlgorithm(), map);
//
//    std::pair<double, double> start = robotWrapper->getCurrentPosition();
//    route->setStartingPoint(start);
//    route->setGoalPoint(roomHandler.getRooms()[0].getCenterPoint());
//
//    route->createPath();
//    std::vector<std::pair<double, double> > path = route->getLatestPath();
//    robotWrapper->setCurrentPath(path);
//    for (int i = 1; i < path.size(); i++) {
//        //     rotation to the point
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
//    thread->join();
//    return 0;
//=======


using namespace PlayerCc;
std::thread* stageThread;
// signal keyboard ctrl+c handler
void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
    // cleanup and close up stuff here
    // terminate program
    if(stageThread != nullptr) {
        pthread_kill(stageThread->native_handle(), SIGINT);
    }
    exit(signum);
}

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

void launch_robotCLI(std::thread* stageThread) {
    std::string mapGeneratorPath = getAbsolutePath("../maps/fromServer.png");
    auto *map = new MapGenerator("../maps/fromServer.png");

//    PlayerClient client("localhost", 6665);
//    Position2dProxy position(&client, 0);
//    RangerProxy laser(&client, 1);
    std::string path = "localhost";
    auto* robotWrapper = new RobotWrapper(path, 6665, path);
    std::string pathToRoomsConfig = getAbsolutePath("../configurations/room_coordinates.txt");
    auto* robotPlanner = new RobotPlanner("../configurations/room_coordinates.txt", robotWrapper, map);
    auto* robotCLI = new RobotCLI(robotPlanner);
    robotCLI->setStageThread(stageThread);
    robotCLI->run();
}

void start_program() {
    stageThread = new std::thread(runStageScript);
    std::cout << "Launch robot's CLI? [Y/n]: ";
    std::string answer;
    std::cin >> answer;
    std::cout << std::endl;
    if (answer == "Y" || answer == "y") {
        std::cout << "Launching robot's CLI..." << std::endl << std::endl;
        // Clear the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.clear();
        launch_robotCLI(stageThread);
    } else {
        std::cout << "Exiting robot's CLI launcher..." << std::endl;
    }
    std::cout << "waiting for stage to finish..." << std::endl;
    stageThread->join();
}

//void unitTesting() {
//
////    std::thread stageThread(runStageScript);
////    std::cout << "Continue execution? [Y/n]: ";
////    std::string answer;
////    std::cin >> answer;
////    std::cout << std::endl;
////    if (answer == "Y" || answer == "y") {
////        PlayerClient client("localhost", 6665);
////        Position2dProxy position(&client, 0);
////        RangerProxy laser(&client, 1);
////        auto* robotWrapper = new RobotWrapper(client, position, laser);
////        std::string pathToRoomsConfig = getAbsolutePath("../configurations/room_coordinates.txt");
////        auto* roomsContainer = new RoomsContainer(pathToRoomsConfig);
////        auto* enterRoom = new EnterRoomBehavior(robotWrapper, roomsContainer->getRoomById(1));
////        enterRoom->execute();
////        auto* exitBehavior = new ExitRoomBehavior(robotWrapper, roomsContainer->getRoomById(1));
////        exitBehavior->execute();
//    }
//
////    std::cout << "waiting for stage to finish..." << std::endl;
////    stageThread.join();
//}


int main() {

//    testExit();
//    testNavigation();
//    unitTesting();
    // setting the signal handler
    signal(SIGINT, signalHandler);

    start_program();
    return 0;
}