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

void drawBlock(cv::Mat& map, int x, int y, int blockSize) {
    for (int i = x; i < x + blockSize; i++) {
        for (int j = y; j < y + blockSize; j++) {
            map.at<uchar>(j, i) = 255; // Set to a higher value (255) for better visibility
        }
    }
}

void printToFile(std::string filename, cv::Mat& map) {
    std::ofstream file;
    file.open(filename);
    for (int i = 0; i < map.rows; i++) {
        for (int j = 0; j < map.cols; j++) {
            file << (int)map.at<uchar>(i, j) << " ";
        }
        file << std::endl;
    }
    file.close();
}



int main(int argc, char **argv) {

    // creating mapGenerator
    MapGenerator* map = new MapGenerator("/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/maps/room_map.png");
    auto mapMatrix = map->getBinaryMatrix();
    // creating Route
    Route* route = new Route(new RRTStarAlgorithm(), map);

    // room 1 -18.2 3.5
    // room 10 13.5 3.5
    route->setStartingPoint(std::make_pair(-18, 3.5));
    route->setGoalPoint(std::make_pair(13.5, -5));

    // creating Navigation
    route->createPath();

    // getting route
    auto matrixPath = route->matrixPoint();

    // drawing the path in the matrix
    for (auto point : matrixPath) {
        // drawing to the mapMatrix the values
        drawBlock(mapMatrix, point.first, point.second, 3);
        std::cout << "drawing the path: " <<point.first << " , " << point.second << std::endl;
    }


    for (auto point : route->getLatestPath()) {
        // drawing to the mapMatrix the values
        std::cout << point.first << " " << point.second << std::endl;
    }

    // printing to file
    printToFile("/home/omer/Desktop/Programming/Robot/Robot-Navigation-Workshop/maps/matrix.txt", mapMatrix);

    cv::imshow("map", map->getBinaryMatrix());
    cv::waitKey(0);

}
