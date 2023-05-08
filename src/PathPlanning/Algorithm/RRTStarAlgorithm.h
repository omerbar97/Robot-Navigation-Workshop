//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_RRTSTARALGORITHM_H
#define ROBOT_NAVIGATION_WORKSHOP_RRTSTARALGORITHM_H
#include "Algorithm.h"

class RRTStarAlgorithm : public Algorithm{
public:

    // constructor
    RRTStarAlgorithm(GridMap* gridMap);
    ~RRTStarAlgorithm();

    // override
    void calculate() override;

};

#endif //ROBOT_NAVIGATION_WORKSHOP_RRTSTARALGORITHM_H
