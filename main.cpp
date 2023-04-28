#include <iostream>
#include <libplayerc++/playerc++.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "src/MapGenerator.h"



int main(int argc, char **argv) {

//    cv::Mat image = cv::imread("map.bmp",cv::ImreadModes::IMREAD_COLOR);
//
//    // Set up the PlayerClient object
//    PlayerCc::PlayerClient client("localhost", 6665);
//    PlayerCc::Position2dProxy position(&client, 0);
//
//    // Attempt to connect to the server
//    std::cout << "Connecting to Player/Stage server..." << std::endl;
//    std::cout << "Successfully connected to Player/Stage server." << std::endl;
//
//    // Wait for data to be available
//    while(true) {
//        client.Read();
//        position.SetSpeed(0.2, 0);
//        // Wait for a few seconds
//        sleep(2);
//
//        // Print the robot's position
//        std::cout << "Robot position: (" << position.GetXPos() << ", " << position.GetYPos() << ")" << std::endl;
//    }


    //checking the mapgenerator and naviagation class
    // Create a MapGenerator object
    MapGenerator mapGenerator("/usr/local/share/stage/worlds/bitmaps/889_05.png", 1);
    cv::Mat image = mapGenerator.getBinaryMatrix();
    cv::imshow("test", image);
//    mapGenerator.textToStr("/usr/local/share/stage/worlds/bitmaps/889_05.png");
    cv::waitKey(0);
    return 0;
}
