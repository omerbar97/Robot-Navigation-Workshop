//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ASTARALGORITHM_H
#define ROBOT_NAVIGATION_WORKSHOP_ASTARALGORITHM_H
#include "Algorithm.h"

class AStarAlgorithm : public Algorithm{
public:

    // constructor
    AStarAlgorithm(GridMap* gridMap);
    ~AStarAlgorithm();

    // override
    void calculate() override;

};


#endif //ROBOT_NAVIGATION_WORKSHOP_ASTARALGORITHM_H
