//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ASTARALGORITHM_H
#define ROBOT_NAVIGATION_WORKSHOP_ASTARALGORITHM_H
#include "Algorithm.h"
#include <ompl/geometric/planners/astar/AStar.h>


class AStarAlgorithm : public Algorithm{
public:

    /**
     * constructor for the AStarAlgorithm class.
     * @param gridMap - the grid map to navigate on. (the map is not owned by the class) it will be deleted by the user.
     */
    AStarAlgorithm(GridMap* gridMap);

    /**
     * destructor for the AStarAlgorithm class.
     */
    ~AStarAlgorithm();

    /**
     * calculating the path from the start point to the end point. using the AStarAlgorithm.
     */
    void calculate() override;

};


#endif //ROBOT_NAVIGATION_WORKSHOP_ASTARALGORITHM_H
