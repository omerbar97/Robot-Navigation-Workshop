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

//    // creating mapGenerator
    MapGenerator *map = new MapGenerator(
            "/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/maps/csMap.png");
//    auto mapMatrix = map->getBinaryMatrix();
//    // creating Route
//    Route* route = new Route(new RRTStarAlgorithm(), map);
//
//    // room 1 -18.2 3.5
//    // room 10 13.5 3.5
//    route->setStartingPoint(std::make_pair(-13, 19));
//    route->setGoalPoint(std::make_pair(14, 13));
//
//    // creating Navigation
//    route->createPath();
//
//    // getting route
//    auto matrixPath = route->matrixPoint();
//
//    // drawing the path in the matrix
//    for (auto point : matrixPath) {
//        // drawing to the mapMatrix the values
//        drawBlock(mapMatrix, point.first, point.second, 3);
//        std::cout << "drawing the path: " <<point.first << " , " << point.second << std::endl;
//    }
//
//
////    for (auto point : route->getLatestPath()) {
////        // drawing to the mapMatrix the values
////        std::cout << point.first << " " << point.second << std::endl;
////    }
//
//    // printing to file
////    printToFile("/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/maps/matrix.txt", mapMatrix);
//
//    cv::imshow("map", map->getBinaryMatrix());
//    cv::waitKey(0);


    RoomsHandler roomHandler(
            "/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/configures/room_coordinates.txt", {2});
//    PlayerCc::PlayerClient* client = new PlayerCc::PlayerClient("localhost");
//    RobotWrapper* robotwrapper = new RobotWrapper(client);
//    PlayerCc::Position2dProxy position2DProxy(client);
    PlayerCc::PlayerClient client("localhost", 6665);
    PlayerCc::Position2dProxy position(&client, 0);
    std::cout << position.GetYaw() << std::endl;

//    PlayerCc::LaserProxy laser(&client, 0);
    RobotWrapper* robotWrapper = new RobotWrapper(client, position);

//    // create path
//    Route *route = new Route(new RRTStarAlgorithm(), map);
//
//    // setting the starting point
//    client.Read();
//    std::pair<double, double> start = robotWrapper->getCurrentPosition();
//    route->setStartingPoint(start);
//    route->setGoalPoint(roomHandler.getRooms()[0].getCenterPoint());
//
//    route->createPath();
//    std::vector<std::pair<double, double> > path = route->getLatestPath();
//    for(int i = 1; i < path.size(); i++) {
//        std::cout << path[i].first << " , " << path[i].second << std::endl;
//    }
//    for(int i = 1; i < path.size(); i++) {
//        //     rotation to the point
//        RotationBehavior rotationBehavior(robotWrapper, path[i]);
//        rotationBehavior.execute();
//        HallNavigateBehavior hallNavigateBehavior(robotWrapper, path[i]);
//        hallNavigateBehavior.execute();
//
//    }

    double x,y;
    while(true) {
        std::cout << "enter two point to rotate to";
        std::cin >> x >> y;
        RotationBehavior rotationBehavior(robotWrapper, std::make_pair(x, y));
        rotationBehavior.execute();
    }

}
