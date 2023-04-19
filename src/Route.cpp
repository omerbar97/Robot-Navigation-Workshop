//
// Created by omer on 4/19/23.
//


#include "Route.h"

Route::Route(std::string pathToBmpMap) {
    this->map = new Map(pathToBmpMap);
    this->startPosition = std::make_pair(0, 0);
    this->endPosition = std::make_pair(0, 0);
    this->algorithmCurrentPosition = std::make_pair(0, 0);
    this->directions = std::vector<std::pair<int, int>>();
}

Route::~Route() {
    delete this->map;
}


std::vector<std::pair<float, float>> Route::createRoute() {
    return this->createRoute(this->startPosition, this->endPosition);
}

std::vector<std::pair<float, float>> Route::createRoute(std::pair<float, float> start, std::pair<float, float> end) {

    // initlizing the new route
    this->startPosition = start;
    this->endPosition = end;

    const int width = Map.matrix.getWidth;
    const int height = Map.matrix.getHeight;

    // initlizing the new route
    std::array<std::array<Pixel, width>, height> routeMap = new std::array<std::array<Pixel, width>, height>;

    // creating priority queue
    std::priority_queue<Pixel *> *minHeap = new std::priority_queue<Pixel *>;

    // initlizing the routeMap
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Pixel &t = routeMap[i][j];
            if (routeMap[i][j] == 0) {
                t.isWall = true;
            } else {
                t.isWall = false;
            }
            t.x = i;
            t.y = j;
            t.distance = INT32_MAX;
            t.visited = false;
            minHeap->push(&t);
        }
    }

    // initializing the start point
    Pixel &startPixel = routeMap[start.first][start.second];
    startPixel.distance = 0;

    // while the priority queue is not empty
    while (!minHeap->empty()) {
        Pixel *t = dynamic_cast<Pixel *>(minHeap->top());
        minHeap->pop();
        t->visited = true;

    }

}


void Route::initMap() {
    // need to do
}

void Route::initPriorityQueue(std::priority_queue<Pixel> &min_heap, Pixel &startPixel) {

}

void Route::relaxNeighbors(Pixel &parent, Pixel &neighbor) {
    if (neighbor.distance > parent.distance + 1) {
        neighbor.distance = parent.distance + 1;
        neighbor.parent = &parent;
    }
}

std::vector<Pixel *> Route::getNeighbors(Pixel &parent) {
    std::vector<Pixel *> neighbors;
    int x = parent.x;
    int y = parent.y;
    if (this->map[x + 1][y + 1] == 0) {
        neighbors.push_back(this->map[x + 1][y + 1]);
    }
    if (x + 1 < this->map->getWidth()) {
        neighbors.push_back(this->map->getPixel(x + 1, y));
    }
    if (x - 1 >= 0) {
        neighbors.push_back(this->map->getPixel(x - 1, y));
    }
    if (y + 1 < this->map->getHeight()) {
        neighbors.push_back(this->map->getPixel(x, y + 1));
    }
    if (y - 1 >= 0) {
        neighbors.push_back(this->map->getPixel(x, y - 1));
    }
    return neighbors;
}


