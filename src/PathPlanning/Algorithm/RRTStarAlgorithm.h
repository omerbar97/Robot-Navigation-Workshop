//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_RRTSTARALGORITHM_H
#define ROBOT_NAVIGATION_WORKSHOP_RRTSTARALGORITHM_H
#include "Algorithm.h"

class RRTStarAlgorithm : public Algorithm{
public:

    /**
     * constructor for the RRTStarAlgorithm class. (RRT* algorithm) - Rapidly-exploring Random Tree
     * @param gridMap - the grid map to navigate on. (the map is not owned by the class) it will be deleted by the user.
     */
    RRTStarAlgorithm(GridMap* gridMap);

    /**
     * destructor for the RRTStarAlgorithm class.
     */
    ~RRTStarAlgorithm();

    // override
    void calculate() override;

};

#endif //ROBOT_NAVIGATION_WORKSHOP_RRTSTARALGORITHM_H
