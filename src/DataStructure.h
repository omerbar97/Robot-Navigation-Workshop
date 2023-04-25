//
// Created by omer on 4/19/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_DATASTRUCTURE_H
#define ROBOT_NAVIGATION_WORKSHOP_DATASTRUCTURE_H

struct Pixel {
    int x;
    int y;
    int distance;
    Pixel* parent;
    bool isWall;
    bool visited;

    Pixel(int x = 0, int y = 0, int distance = 0, bool isWall = false, Pixel* parent = nullptr, bool visited = false)
            : x(x), y(y), distance(distance), parent(parent), isWall(isWall), visited(visited) {}

    bool operator<(const Pixel& other) const {
        if(!this->isWall && !other.isWall) {
            return distance < other.distance;
        }
        return false;
    }
    bool operator>(const Pixel& other) const {
        if(!this->isWall && !other.isWall) {
            return distance > other.distance;
        }
        return false;
    }

    bool operator==(const Pixel& other) const {
        return this->x == other.x && this->y == other.y;
    }
};



#endif //ROBOT_NAVIGATION_WORKSHOP_DATASTRUCTURE_H
