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

    Pixel(int x, int y, int distance, bool canPass) : x(x), y(y), distance(distance), canPass(canPass) {}

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
};



#endif //ROBOT_NAVIGATION_WORKSHOP_DATASTRUCTURE_H
