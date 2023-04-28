//
// Created by shilopadael on 4/19/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_MAPGENERATOR_H
#define ROBOT_NAVIGATION_WORKSHOP_MAPGENERATOR_H
#include <string>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <fstream>

class MapGenerator {
private:
    std::string room_map;
    cv::Mat binaryMatrix;
    cv::Mat image;

    // Converts the loaded image to a binary matrix
    // Functionality:
    // - Uses OpenCV's threshold() function to create a binary matrix from the loaded image
    // - Inverts the binary matrix using THRESH_BINARY_INV flag
    // - Applies dilation to fill in gaps in the binary matrix
    // - Sets the binary matrix using setBinaryMatrix() function
    void pngToMatrix();
    int sailSIze;



public:
    // Saves the binary matrix to a text file
    // Parameters:
    // - pathToSave: Path to the text file where the matrix values will be saved
    // Functionality:
    // - Opens a text file using ofstream
    // - Iterates through the binary matrix and writes the values to the text file
    // - Closes the text file
    void matrixToText(std::string pathToSave);

    // Reads binary string text from a file
    // Parameters:
    // - filename: Path to the text file containing the binary string
    // Returns:
    // - Binary string read from the text file
    // Functionality:
    // - Opens a text file using ifstream
    // - Reads the lines from the text file and concatenates them to form the binary string
    // - Closes the text file
    std::string textToStr(std::string filename);

    // Function: binaryStrToBmp
    // Description: Convert a binary string to an image in BMP format
    // Input:
    //   binaryString: Binary string representing the image (0s and 1s)
    //   path: Path to save the BMP image file
    // Output: None
    void binaryStrToBmp(std::string binaryString, std::string path);

    // Constructor for MapGenerator class
    // Parameters:
    // - pngImage: Path to the PNG image file used for generating the map
    // - defaultArg: Optional argument with default value of 1
    // Functionality:
    // - Sets the room map by calling setRoomMap() with pngImage parameter
    // - Sets the sail size to 1
    // - Calls setImage() to load and resize the image
    // - Calls pngToMatrix() to convert the image to a binary matrix
    MapGenerator(std::string pngImage , int sailSIze = 1);

    // Getter for room_map
    std::string getRoomMap() const;

    // Setter for room_map
    void setRoomMap(const std::string& map);

    // Getter for binaryMatrix
    cv::Mat getBinaryMatrix() const;

    // Setter for binaryMatrix
    void setBinaryMatrix(const cv::Mat& matrix);
    // Getter for sailSIze
    int getSailSize() const;

    // Setter for sailSIze
    void setSailSize(int size);
    // Getter for image
    cv::Mat getImage() const;

    // Setter for image
    int setImage();

};



#endif //ROBOT_NAVIGATION_WORKSHOP_MAPGENERATOR_H
