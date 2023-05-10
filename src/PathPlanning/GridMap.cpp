//
// Created by omer on 5/8/23.
//

#include "GridMap.h"

GridMap::GridMap(cv::Mat *pixelMap, int scale) {
//    initGridMap(pixelMap, scale);
    this->gridMatrix = pixelMap;
    this->width = gridMatrix->cols;
    this->height = gridMatrix->rows;

    // setting ompl state space
    setName("2dGridMap");
    setBounds(0, 255); // matrix value can be 0 or 255
    addDimension("x", 0, width - 1);
    addDimension("y", 0, height - 1);
}

int GridMap::getWidth() const {
    return this->width;
}

int GridMap::getHeight() const {
    return this->height;
}

void GridMap::setGridMatrix(cv::Mat *gridMatrix) {
    // deleting the old one
    if(this->gridMatrix != nullptr) {
        delete(this->gridMatrix);
    }

    this->gridMatrix = gridMatrix;
    this->width = this->gridMatrix->cols;
    this->height = this->gridMatrix->rows;
}

GridMap::~GridMap() {
    if(this->gridMatrix != nullptr) {
        delete(this->gridMatrix);
    }
}

GridMap::GridMap(const GridMap &gridMap) {
    this->gridMatrix = new cv::Mat(*gridMap.gridMatrix);
    this->width = gridMap.width;
    this->height = gridMap.height;
    this->scale = gridMap.scale;
}

cv::Mat *GridMap::getGridMatrix() const {
    return this->gridMatrix;
}
