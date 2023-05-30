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


    MapGenerator *map = new MapGenerator(
            "/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/robot-client/maps/csMap.png");

    RoomsHandler roomHandler(
            "/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/robot-client/configures/room_coordinates.txt", {2});
    PlayerCc::PlayerClient client("localhost", 6665);
    PlayerCc::Position2dProxy position(&client, 0);
    PlayerCc::RangerProxy laser(&client, 1);
//    client.Read();

    std::list<playerc_device_info_t> t = client.GetDeviceList();


    for(auto i : t) {
        std::cout << "drivername: " << i.drivername << std::endl;
        std::cout << "index " << i.addr.index << std::endl;
    }
    std::cout << position.GetYaw() << std::endl;

    RobotWrapper* robotWrapper = new RobotWrapper(client, position, laser);

    // create path
    Route *route = new Route(new RRTStarAlgorithm(), map);

    std::pair<double, double> start = robotWrapper->getCurrentPosition();
    route->setStartingPoint(start);
    route->setGoalPoint(roomHandler.getRooms()[0].getCenterPoint());

    route->createPath();
    std::vector<std::pair<double, double> > path = route->getLatestPath();
    for(int i = 1; i < path.size(); i++) {
        //     rotation to the point
        std::cout << "rotation to the point: " << path[i].first << " , " << path[i].second << std::endl;
        RotationBehavior rotationBehavior(robotWrapper, path[i]);
        rotationBehavior.execute();
        std::cout << "navigate to point: " << path[i].first << " , " << path[i].second << std::endl;
        HallNavigateBehavior hallNavigateBehavior(robotWrapper, path[i]);
        hallNavigateBehavior.execute();

    }

//    Server server("localhost", 8080);
//    std::thread* serverThread;
//    if(server.init()) {
//        serverThread = new std::thread(&Server::acceptConnection, &server);
//        serverThread->detach();
//        while(true) {
//            std::string n;
//            std::cin >> n;
//            server.send(n);
//            server.recv();
//        }
//    }

//    VoiceMessageBehavior voiceMessageBehavior("ofir ve shilo ya-manyakym", "kamika");
//    voiceMessageBehavior.execute();

    return 0;

}
