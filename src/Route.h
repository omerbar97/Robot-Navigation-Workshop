//
// Created by omer on 4/19/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROUTE_H
#define ROBOT_NAVIGATION_WORKSHOP_ROUTE_H

#include <utility>
#include <vector>
#include <string>
#include <array>
#include "DataStructure.h"
#include <queue>

#define WALL 0
class Route {

private:
    // private variables

    Map *map;
    std::pair<float, float> startPosition;
    std::pair<float, float> endPosition;
    std::pair<float, float> algorithmCurrentPosition;
    std::vector<std::pair<int, int>> directions;

    // private methods

    /**
     * when first creating an instance of Route, initlizing the Map object.
     */
    void initMap();

    /**
     * calculate the nextPoint for the robot to go given Map, startPos, endPos and current position.
     * @return
     */
    std::pair<float, float> calculateNextPoint();

    void initPriorityQueue(std::priority_queue<Pixel> &min_heap, Pixel &startPixel);

    void relaxNeighbors(Pixel &parent, Pixel &neighbor);


    template <typename T, size_t WIDTH, size_t HEIGHT>
    std::vector<Pixel*> getNeighbors(Pixel &parent, std::array<std::array<T, WIDTH>, HEIGHT> &routeMap);

    void addNeighborsToQueue(std::vector<Pixel *> neighbors, std::priority_queue<Pixel> &minHeap);

public:


    Route(std::string pathToBmpMap);

    ~Route();

    /**
     * return vectors of pairs, each one is the robot step to the current route.
     * @return vectors of pairs.
     */
    std::vector<std::pair<float, float>> createRoute();

    /**
     * return vectors of pairs, each one is the robot step to the current route. and by initializing the new variables
     * @param start std::pair<float, float>
     * @param endstd::pair<float, float>
     * @return vectors of paris.
     */
    std::vector<std::pair<float, float>> createRoute(std::pair<float, float> start, std::pair<float, float> end);

    /**
     * setting the new route starting position
     * @param x float
     * @param y float
     */
    void setStartPosition(float x, float y);

    /**
     * setting the new route ending position
     * @param x
     * @param y
     */
    void setEndPosition(float x, float y);

    /**
     * return the current route starting position
     * @return std::pair<float, float>
     */
    std::pair<float, float> getStartPosition();

    /**
     * return the current route ending position
     * @return  std::pair<float, float>
     */
    std::pair<float, float> getEndPosition();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROUTE_H
