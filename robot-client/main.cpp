#include <iostream>
#include <libplayerc++/playerc++.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "src/Resources/MapGenerator.h"
#include "src/Navigate/Navigation.h"
#include "src/PathPlanning/Route.h"
#include "src/PathPlanning/Algorithm/RRTStarAlgorithm.h"
#include "src/Resources/RoomsHandler.h"
#include "src/Robot/RobotWrapper.h"
#include "src/Behavior/RobotBehavior/HallNavigateBehavior.h"
#include "src/Behavior/RobotBehavior/RotationBehavior.h"
#include "src/Behavior/MessageBehavior/VoiceMessageBehavior.h"
#include <string>

void drawBlock(cv::Mat &map, int x, int y, int blockSize) {
    for (int i = x; i < x + blockSize; i++) {
        for (int j = y; j < y + blockSize; j++) {
            map.at<uchar>(j, i) = 255; // Set to a higher value (255) for better visibility
        }
    }
}

void printToFile(std::string filename, cv::Mat &map) {
    std::ofstream file;
    file.open(filename);
    for (int i = 0; i < map.rows; i++) {
        for (int j = 0; j < map.cols; j++) {
            file << (int) map.at<uchar>(i, j) << " ";
        }
        file << std::endl;
    }
    file.close();
}

using namespace PlayerCc;

int main(int argc, char **argv) {
    if (argc != 4) {
        // error
        std::cout << "Error: invalid number of arguments" << std::endl;
        return 1;
    }

    MapGenerator *map = new MapGenerator(
            "/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/robot-client/maps/fromServer.png");

    RoomsHandler roomHandler(
            "/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/robot-client/configures/room_coordinates.txt",
            {3});
    int port = strtol(argv[2], nullptr, 10);
    std::cout << "port: " << port << std::endl;
    std::cout << "ip: " << argv[1] << std::endl;
//    if(port < 0 || port > 65535) {
//        std::cout << "Error: invalid port number" << std::endl;
//        return 1;
//    }
    std::string ip = argv[1];
    PlayerCc::PlayerClient client(ip, port);
    PlayerCc::Position2dProxy position(&client, 0);
    PlayerCc::RangerProxy laser(&client, 1);

    std::list<playerc_device_info_t> t = client.GetDeviceList();


    std::cout << position.GetYaw() << std::endl;

    RobotWrapper *robotWrapper = new RobotWrapper(client, position, laser, "ws://localhost:8081");

    // Run a member function of robotWrapper in a separate thread
    std::thread* thread1, *thread2;
    if (robotWrapper->getWsClient() != nullptr) {
        usleep(1000000);
        thread2 = new std::thread([robotWrapper]() {
            robotWrapper->sendRobotPosition();
        });
    }

    // create path
    Route *route = new Route(new RRTStarAlgorithm(), map);

    std::pair<double, double> start = robotWrapper->getCurrentPosition();
    route->setStartingPoint(start);
    route->setGoalPoint(roomHandler.getRooms()[0].getCenterPoint());

    route->createPath();
    std::vector<std::pair<double, double> > path = route->getLatestPath();
    for (int i = 1; i < path.size(); i++) {
        //     rotation to the point
        std::cout << "rotation to the point: " << path[i].first << " , " << path[i].second << std::endl;
        RotationBehavior rotationBehavior(robotWrapper, path[i]);
        rotationBehavior.execute();
        std::cout << "navigate to point: " << path[i].first << " , " << path[i].second << std::endl;
        HallNavigateBehavior hallNavigateBehavior(robotWrapper, path[i]);
        hallNavigateBehavior.execute();

    }

    // waiting for thread
//    if (robotWrapper->getWsClient() != nullptr) {
//        thread1->join();
//        thread2->join();
//    }
    return 0;

}
