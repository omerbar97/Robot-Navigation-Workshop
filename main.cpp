#include <iostream>
#include <libplayerc++/playerc++.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "src/MapGenerator.h"
#include "src/Navigation.h"


void stageToPixel(double x, double y, int &pixel_x, int &pixel_y, double scale) {
    // The dimensions of the stage map
    const int blockWidthHeight = 1086 / 40;
    const int blockWidthHeightPixel = 443 / 18;

    // Convert the x-coordinate to pixel coordinate
    pixel_x = static_cast<int>((x + 40 / 2) * blockWidthHeight);

    // Convert the y-coordinate to pixel coordinate
    pixel_y = static_cast<int>((18 / 2 - y) * blockWidthHeightPixel);
}

void pixelToStage(int pixel_x, int pixel_y, double &x, double &y, double scale) {
    // The dimensions of the stage map
    const int blockWidthHeight = 1086 / 40;
    const int blockWidthHeightPixel = 443 / 18;

    // Convert the pixel x-coordinate to stage coordinate
    x = (static_cast<double>(40 / 2) * blockWidthHeight - static_cast<double>(pixel_x)) / (-blockWidthHeight);
    // Convert the pixel y-coordinate to stage coordinate
    y = (static_cast<double>(18 / 2)* blockWidthHeightPixel - static_cast<double>(pixel_y)) / blockWidthHeightPixel;
}

void drawBlock(cv::Mat &image, int x, int y, int width, int height) {
    // Draw the block
    for(int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            image.at<uchar>(y + j, x + i) = 100;
        }
    }
}

void drawNewColor(cv::Mat &pngImage, cv::Mat &binaryMatrix) {
    // Draw the block
    for(int i = 0; i < pngImage.rows; i++) {
        for (int j = 0; j < pngImage.cols; j++) {
            // getting the color from pngImage
            cv::Vec3b color = pngImage.at<cv::Vec3b>(i, j);  // get color vector
//            std::cout << "color: " << color << std::endl;
            if(color[0] == 255 && color[1] == 255 && color[2] == 255) {
                // the matrix is white
                // checking if the binary matrix value is not 0
                if(binaryMatrix.at<uchar>(i, j) != 0) {
                    // the binary matrix value is not 0
                    // setting the color to red
                    drawBlock(pngImage, j, i, 1, 1);
                }
            }
        }
    }
}

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
    cv::Mat& image = mapGenerator.getBinaryMatrix();
    cv::Mat& pngImage = mapGenerator.getImage();
    std::cout << "image size: " << image.size() << std::endl;

    double x = -18;
    double y = 3;

    int pixel_x;
    int pixel_y;

    drawNewColor(pngImage, image);

    cv::imshow("pngImage", pngImage);
    cv::imshow("binaryImage", image);
//    mapGenerator.textToStr("/usr/local/share/stage/worlds/bitmaps/889_05.png");
    mapGenerator.matrixToText("../maps/str.txt");
    cv::waitKey(0);
    return 0;
}
