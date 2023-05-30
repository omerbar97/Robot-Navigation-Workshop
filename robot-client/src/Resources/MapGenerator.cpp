//
// Created by shilopadael on 4/19/23.
//


#include "MapGenerator.h"



MapGenerator::MapGenerator(std::string pngImage , int sailSize) {

    this->setRoomMap(pngImage);
    this->sailSIze = sailSize;
    setImage();
    pngToMatrix();
    this->classifiedMatrix = cv::Mat(this->binaryMatrix.size(), CV_32SC2);
    for (int row = 0; row < this->binaryMatrix.rows; ++row) {
        for (int col = 0; col < this->binaryMatrix.cols; ++col) {
            this->classifiedMatrix.at<cv::Vec2i>(row, col)[0] = this->binaryMatrix.at<uchar>(row, col);
            this->classifiedMatrix.at<cv::Vec2i>(row, col)[1] = classifyCell(row, col);
        }
    }
}
int MapGenerator::classifyCell(int row, int col) {


// TODO: Define the function to classify the scopes in the map Classify the cell based on the binary matrix
    // Functionality:
    // - Check if the cell is a wall
    // - Check if the cell is a door
    // - Check if the cell is an exit
    // - Check if the cell is an entry
    // - Check if the cell is a hallway
    // - Return the classification
    if (this->binaryMatrix.at<uchar>(row, col) == WALL) {
        return WALL;
    } else if (this->binaryMatrix.at<uchar>(row, col) == DOOR) {
        return DOOR;
    } else if (this->binaryMatrix.at<uchar>(row, col) == EXIT_POINT) {
        return EXIT_POINT;
    } else if (this->binaryMatrix.at<uchar>(row, col) == ENTRY_POINT) {
        return ENTRY_POINT;
    } else {
        return HALLWAY;
    }
}

void MapGenerator::pngToMatrix() {
    // Convert the image to a binary matrix
    cv::Mat binaryMatrix;
    cv::threshold(getImage(), binaryMatrix, 2, 255, cv::THRESH_BINARY_INV); // Use THRESH_BINARY_INV to invert the binary matrix
    // Apply image dilation to fill in gaps
    int dilationSize = 1; // Set dilation size (in pixels)
    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2 * dilationSize + 1, 2 * dilationSize + 1));
    cv::dilate(binaryMatrix, binaryMatrix, element);
    this->setBinaryMatrix(binaryMatrix);
}

void MapGenerator::matrixToText(std::string pathToSave) {
    // Save matrix values to a text file
    std::ofstream outFile(pathToSave);
    if (outFile.is_open()) {
        for (int row = 0; row < getImage().rows; ++row) {
            for (int col = 0; col < getImage().cols; ++col) {
                outFile << (binaryMatrix.at<uchar>(row, col) > 0 ? 1 : 0);
            }
            outFile << std::endl;
        }
        outFile.close();
        std::cout << "Matrix values saved to"<< pathToSave << std::endl;
    } else {
        std::cerr << "Failed to save matrix values to" << pathToSave << std::endl;
    }
}



std::string MapGenerator::textToStr(std::string filename) {
// Read binary string text from file
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open matrix.txt" << std::endl;
        return nullptr;
    }
    std::string binaryString;
    std::string line;
    while (std::getline(inFile, line)) {
        binaryString += line;
    }
    inFile.close();
    return binaryString;

}

void MapGenerator::binaryStrToBmp(std::string binaryString, std::string path) {

// Create image matrix
    cv::Mat image2(image.rows, image.cols, CV_8UC1);

// Loop through binary string and set pixel values in image
    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
            uchar pixelValue = (binaryString[row * image.cols + col] == '1') ? 255 : 0;
            image2.at<uchar>(row, col) = pixelValue;
        }
    }

// Save image to BMP
    cv::imwrite(path, image2);
    std::cout << "Image saved to" << path << " : " << std::endl;

}

std::string MapGenerator::getRoomMap() const {
    return this->room_map;
}

void MapGenerator::setRoomMap(const std::string &map) {
    this->room_map = map;
}

void MapGenerator::setBinaryMatrix(cv::Mat matrix) {
    this->binaryMatrix = matrix;

}

cv::Mat MapGenerator::getBinaryMatrix() {
    return this->binaryMatrix;
}

int MapGenerator::getSailSize() const {
    return this->sailSIze;
}

void MapGenerator::setSailSize(int size) {
    this->sailSIze = size;
}

cv::Mat& MapGenerator::getImage() {
    return this->image;
}

int MapGenerator::setImage() {
    this->image = cv::imread(getRoomMap(), cv::IMREAD_GRAYSCALE);
    // Check if the image was loaded successfully
    if (image.empty()) {
        // Image not loaded, handle the error
        std::cerr << "Failed to load image!" << std::endl;
        return -1;
    }
    // Calculate the number of cells in the resized matrix
    int numRows = image.rows;
    int numCols = image.cols;

    // Resize the image to the desired size
    cv::Size newSize(numCols / getSailSize(), numRows / getSailSize());
    cv::resize(image, image, newSize);
}

//void MapGenrator::binaryStrToBmp(std::string binaryString, std::string path) {
//    // Calculate number of rows and columns based on the length of binary string
//    int numCols = 0;
//    int numRows = 1;
//    for (char c : binaryString) {
//        if (c == '\n') {
//            ++numRows;
//        } else {
//            ++numCols;
//        }
//    }
//
//    // Create image matrix
//    cv::Mat image2(numRows, numCols, CV_8UC1);
//
//    int row = 0;
//    int col = 0;
//
//    // Loop through binary string and set pixel values in image
//    for (char c : binaryString) {
//        if (c == '\n') {
//            ++row;
//            col = 0;
//            continue;
//        }
//
//        uchar pixelValue = (c == '1') ? 255 : 0;
//        image2.at<uchar>(row, col) = pixelValue;
//        ++col;
//    }
//
//    // Save image to BMP
//    cv::imwrite(path, image2);
//
//    std::cout << "Image saved to" << path << " : " << std::endl;
//}














//// Load PNG image
// Getter for room_map

//// Set the desired sail size (1x1 pixels)
//int sailSize = 1;
//

//
//





//void MapGenrator::binaryStrToBmp(std::string binaryString, std::string path) {
//// Create image matrix
//    cv::Mat image2(numRows, numCols, CV_8UC1);
//
//// Loop through binary string and set pixel values in image
//    for (int row = 0; row < numRows; ++row) {
//        for (int col = 0; col < numCols; ++col) {
//            uchar pixelValue = (binaryString[row * numCols + col] == '1') ? 255 : 0;
//            image2.at<uchar>(row, col) = pixelValue;
//        }
//    }
//
//// Save image to BMP
//    cv::imwrite("image.bmp", image2);
//
//    std::cout << "Image saved to image.bmp" << std::endl;
//
//}








