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

    int startX = (int)start.first;
    int startY = (int)start.second;

    int endX = (int)end.first;
    int endY = (int)end.second;

    const int width = Map.matrix.getWidth;
    const int height = Map.matrix.getHeight;

    // initializing the new route
    std::array<std::array<Pixel*, width>, height>* routeMap = new std::array<std::array<Pixel*, width>, height>;

    // creating priority queue
    auto *minHeap = new std::priority_queue<Pixel *>;

    // initializing the routeMap
    bool wall;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (Map.matrix[i][j] == WALL) {
                wall = true;
            } else {
                wall = false;
            }
            Pixel *t = new Pixel(i, j, INT32_MAX, wall);
            t->visited = false;
            t->parent = nullptr;

            // adding to routeMap
            routeMap[i][j] = t;
        }
    }

    // initializing the start point
    Pixel *startPixel = routeMap[startX][startY];
    Pixel *endPixel = routeMap[endX][endY];

    // setting the start point distance to 0
    startPixel->distance = 0;

    // adding the start point to the priority queue
    minHeap->push(startPixel);

    // while the priority queue is not empty
    while (!minHeap->empty()) {
        // adding all the neighbors of the top pixel to the priority queue
        Pixel *t = dynamic_cast<Pixel *>(minHeap->top());
        if(t == endPixel) {
            // reached to the end
            break;
        }
        t->visited = true;
        minHeap->pop();
        std::vector<Pixel*> neighbors = this->getNeighbors(*t, routeMap);
        this->addNeighborsToQueue(neighbors, reinterpret_cast<std::priority_queue<Pixel> &>(minHeap));
        for (Pixel *neighbor : neighbors) {
            // relaxing the neighbors.
            this->relaxNeighbors(*t, *neighbor);
        }
    }

    // restoring the route
    Pixel* nextPixal = endPixel;
    while(nextPixal->parent != startPixel) {
        this->directions.push_back(std::make_pair(nextPixal->x, nextPixal->y));
        nextPixal = nextPixal->parent;
    }

    // releasing the memory
    for(Pixel* pixel : routeMap) {
        delete pixel;
        pixel == nullptr;
    }
    delete routeMap;
    delete minHeap;
}


void Route::initMap() {
    // need to do
}


void Route::relaxNeighbors(Pixel &parent, Pixel &neighbor) {
    if (neighbor.distance > parent.distance + 1) {
        neighbor.distance = parent.distance + 1;
        neighbor.parent = &parent;
    }
}


void Route::addNeighborsToQueue(std::vector<Pixel*> neighbors, std::priority_queue<Pixel> &minHeap) {
    for (Pixel *neighbor : neighbors) {
        // pixel already checked no wall included.
        minHeap.push(*neighbor);
    }
}


template<typename T, size_t WIDTH, size_t HEIGHT>
std::vector<Pixel*> Route::getNeighbors(Pixel &parent, std::array<std::array<T, WIDTH>, HEIGHT> &routeMap) {
    std::vector<Pixel *> neighbors;
    int x = parent.x;
    int y = parent.y;
    /**
     * 0 1 2
     * 3 * 5
     * 6 7 8
     */
     // getting number 2
     if(x + 1 < WIDTH && !routeMap[x + 1][y + 1]->visited && y + 1 < HEIGHT && !routeMap[x + 1][y + 1].isWall) {
         neighbors.push_back(&routeMap[x + 1][y + 1]);
     }
    // getting number 1
    if(y + 1 < HEIGHT && !routeMap[x][y + 1]->visited && !routeMap[x][y + 1].isWall) {
        neighbors.push_back(&routeMap[x][y + 1]);
    }
    // getting number 0
    if(x - 1 >= 0 && !routeMap[x - 1][y + 1]->visited && y + 1 < HEIGHT && !routeMap[x - 1][y + 1].isWall) {
        neighbors.push_back(&routeMap[x - 1][y + 1]);
    }
    // getting number 3
    if(x - 1 >= 0 && !routeMap[x - 1][y].visited && !routeMap[x - 1][y].isWall) {
        neighbors.push_back(&routeMap[x - 1][y]);
    }
    // getting number 5
    if(x + 1 < WIDTH && !routeMap[x + 1][y].visited &&!routeMap[x + 1][y].isWall) {
        neighbors.push_back(&routeMap[x + 1][y]);
    }
    // getting number 6
    if(x - 1 >= 0 && y - 1 >= 0 && !routeMap[x - 1][y - 1].visited && !routeMap[x - 1][y - 1].isWall) {
        neighbors.push_back(&routeMap[x - 1][y - 1]);
    }
    // getting number 7
    if(y - 1 >= 0 && !routeMap[x][y - 1].visited && !routeMap[x][y - 1].isWall) {
        neighbors.push_back(&routeMap[x][y - 1]);
    }
    // getting number 8
    if(x + 1 < WIDTH && y - 1 >= 0 && !routeMap[x + 1][y - 1].visited && !routeMap[x + 1][y - 1].isWall) {
        neighbors.push_back(&routeMap[x + 1][y - 1]);
    }
    // returning the neighbors
    return neighbors;
}


