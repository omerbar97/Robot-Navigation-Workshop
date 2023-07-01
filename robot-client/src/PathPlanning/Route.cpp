#include "Route.h"

Route::Route(Algorithm *algorithm, MapGenerator *mapGenerator) {
    this->algorithm = algorithm;
    this->mapGenerator = mapGenerator;
    this->cvMap = new cv::Mat(mapGenerator->getBinaryMatrix());
    this->gridMap = new GridMap(cvMap, 1);
    this->matrixWidth = gridMap->getWidth();
    this->matrixHeight = gridMap->getHeight();
    this->numOfBlocksWidth = 16.8*2; // based on the stage blocks
    this->numOfBlocksHeight = 26.7*2; // based on the stage blocks
    initGridMapToAlgorithm();
}

Route::Route(MapGenerator *mapGenerator) {
    this->algorithm = new RRTStarAlgorithm(gridMap);
    this->mapGenerator = mapGenerator;
    this->cvMap = new cv::Mat(mapGenerator->getBinaryMatrix());
    this->gridMap = new GridMap(cvMap, 1);
    this->matrixWidth = gridMap->getWidth();
    this->matrixHeight = gridMap->getHeight();
    this->numOfBlocksWidth = 16.8*2; // based on the stage blocks
    this->numOfBlocksHeight = 26.7*2; // based on the stage blocks
}

void Route::initGridMapToAlgorithm() {
    if(this->gridMap != nullptr && this->algorithm != nullptr) {
        algorithm->setGridMap(gridMap);
    } else {
        // error
        throw std::invalid_argument("gridMap or algorithm can't be null");
    }
}

std::pair<int, int> Route::stageToMatrix(std::pair<double, double> point) const {
    // The dimensions of the stage map
    // The dimensions of the stage map
    const int blockWidthHeight = this->matrixWidth / this->numOfBlocksWidth;
    const int blockWidthHeightPixel = this->matrixHeight / this->numOfBlocksHeight;

    // getting the point
    double x = point.first;
    double y = point.second;

    // Convert the x-coordinate to pixel coordinate
    int pixel_x = static_cast<int>((x + this->numOfBlocksWidth / 2) * blockWidthHeight);
    // Convert the y-coordinate to pixel coordinate
    int pixel_y = static_cast<int>((this->numOfBlocksHeight / 2 - y) * blockWidthHeightPixel);
    return std::pair<int, int>(pixel_x, pixel_y);
}

std::pair<double, double> Route::matrixToStage(std::pair<int, int> point) const {
    // The dimensions of the stage map
    const int blockWidthHeight = this->matrixWidth / this->numOfBlocksWidth;
    const int blockWidthHeightPixel = this->matrixHeight / this->numOfBlocksHeight;

    // getting the point
    int pixel_x = point.first;
    int pixel_y = point.second;

    // Convert the pixel x-coordinate to stage coordinate
    double x = (static_cast<double>(this->numOfBlocksWidth / 2) * blockWidthHeight - static_cast<double>(pixel_x)) / (-blockWidthHeight);
    // Convert the pixel y-coordinate to stage coordinate
    double y = (static_cast<double>(this->numOfBlocksHeight / 2)* blockWidthHeightPixel - static_cast<double>(pixel_y)) / blockWidthHeightPixel;

    return std::pair<double, double>(x, y);
}



void Route::setGridMap(GridMap *gridMap) {
    if(gridMap == nullptr) {
        // error
        throw std::invalid_argument("gridMap can't be null");
    }
    if(this->gridMap != nullptr) {
        delete this->gridMap;
    }
    this->gridMap = gridMap;
    this->matrixWidth = gridMap->getWidth();
    this->matrixHeight = gridMap->getHeight();
    initGridMapToAlgorithm();
}

void Route::setMapGenerator(MapGenerator *mapGenerator) {
    // upon setting new map generator changing the gridMap
    if(mapGenerator == nullptr) {
        // error
        throw std::invalid_argument("mapGenerator can't be null");
    }
    if(this->mapGenerator != nullptr) {
        delete this->mapGenerator;
    }

    // setting new map generator
    this->mapGenerator = mapGenerator;
    if(this->cvMap != nullptr) {
        delete this->cvMap;
    }

    this->cvMap = new cv::Mat(this->mapGenerator->getBinaryMatrix());
    // setting new grid map
    setGridMap(new GridMap(this->cvMap, 1));
    // setting new width and height
    this->matrixWidth = gridMap->getWidth();
    this->matrixHeight = gridMap->getHeight();

    // inserting the gridMap to the algorithm
    initGridMapToAlgorithm();
}

void Route::setAlgorithm(Algorithm *algorithm) {
    if(algorithm == nullptr) {
        // error
        throw std::invalid_argument("algorithm can't be null");
    }
    if(this->algorithm != nullptr) {
        delete this->algorithm;
    }
    this->algorithm = algorithm;
    initGridMapToAlgorithm();
}

void Route::setStartingPoint(std::pair<double, double> start) {
    if(this->algorithm == nullptr) {
        // error
        throw std::invalid_argument("cannot set starting point without algorithm");
    }
    this->algorithm->setStart(stageToMatrix(start));
}

void Route::setGoalPoint(std::pair<double, double> goal) {
    if(this->algorithm == nullptr) {
        // error
        throw std::invalid_argument("cannot set goal point without algorithm");
    }
    this->algorithm->setGoal(stageToMatrix(goal));
}

std::vector<std::pair<double, double>> Route::getStagePath() const {
    // in the algorithm the path is in matrix coordinates

    std::vector<std::pair<int, int>>* matrixPath = this->algorithm->getPath();
    if(matrixPath == nullptr) {
        // error
        std::cout << "couldn't find a path" << std::endl;
        return {};
    }

    std::vector<std::pair<double, double>> stagePath;
    // converting the path to stage coordinates
    for(std::pair<int, int> point : *matrixPath) {
        stagePath.push_back(matrixToStage(point));
    }
    return stagePath;
}

void Route::createPath() {
    // doing all the logic of the algorithm

    this->algorithm->calculate();

    this->cvMap = new cv::Mat(this->mapGenerator->getBinaryMatrix());
    this->gridMap = new GridMap(cvMap, 1);

    // getting the path from the algorithm
    this->latestPath = getStagePath();

}

std::vector<std::pair<double, double>> Route::getLatestPath() const {
    return this->latestPath;
}

std::vector<std::pair<int, int>> Route::matrixPoint() {
    if(this->algorithm->getPath() != nullptr) {
        return *this->algorithm->getPath();
    }
    return {};
}
std::pair<double, double> Route::getGoalPoint() {
    return this->algorithm->getGoal();
}

Route::~Route() {
}
