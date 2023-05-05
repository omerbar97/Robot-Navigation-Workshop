#include <iostream>
#include <libplayerc++/playerc++.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "src/Resources/MapGenerator.h"
#include "src/Navigate/Navigation.h"


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

    // creating RobotWrapper
//    RobotWrapper robotWrapper = new RobotWrapper(double GorundSpeed, double rotataionSpeed);
//
//    // navigation
//    Navigation navigation = new Navigation(Navigatable* robotWrapper,char* pathToMap, char* pathToDataRoom)
//
//    Mission* mission = navigation
//    /**
//     * navigation creates the Route, vector, Room
//     */
//
//    std::cin >> x // string of rooms. 1, 5, 10
//    // 1
//    // 5
//    // 10
//
//
//
//
//    Assignment assignment[]; // 1, 5, 10
//    while(assignment != NULL) {
//        // do the assignment
//        // set the mission
//        // do the mission
//        // set the next mission
//    }
//        // do the assignment
//        // set the mission
//        // do the mission
//        // set the next mission
//    }
//
//    // break x to integers
//
//    for() {
//        mission.setMission(x)
//        // setMission(1) -> setMission(5) -> setMission(10)
//        //
//        mission.doMission();
//    }

}
