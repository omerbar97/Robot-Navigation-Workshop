//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ALGORITHM_H
#define ROBOT_NAVIGATION_WORKSHOP_ALGORITHM_H
#include <ompl/base/SpaceInformation.h>
#include <ompl/base/Planner.h>
#include <ompl/geometric/SimpleSetup.h>
#include "../GridMapValidityChecker.h"
#include "../GridMap.h"

/**
 * @brief The Algorithm class is an abstract class that represents a path planning algorithm. It has a grid map and
 * a planner. It also has a start and goal points and a path. The calculate function is pure virtual and must be
 * implemented by the derived class. The calculate function is responsible for calculating the path and saving it in
 * the path vector. As point x,y in the matrix! the route class need to convert it to the real world coordinates.
 */
class Algorithm {
protected:
    // private members
    /**
     * @brief gridMap is a pointer to the grid map that the algorithm will work on. it includes
     * the OMPL library that does all the calculation for us.
     */
    GridMap* gridMap;

    /**
     * @brief start is the start point of the path.
     */
    std::pair<int ,int> start;

    /**
     * @brief goal is the goal point of the path.
     */
    std::pair<int ,int> goal;

    /**
     * @brief pathInMatrix is a vector of pairs that represents the path in the matrix. each pair is a point x,y in the
     * matrix! the route class need to convert it to the real world coordinates.
     */
    std::vector<std::pair<int ,int>>* pathInMatrix;

    /**
     * @brief pathInVector the OMPL library return the path as ompl::geometric::PathGeometric we will convert it
     * to a matrix path, and save it in the pathInMatrix vector.
     * @param solutionPath
     */
    void transferPathToVector(ompl::geometric::PathGeometricPtr solutionPath);

public:

    Algorithm();

    /**
     * @brief Algorithm constructor. it gets a grid map
     * @param gridMap
     */
    Algorithm(GridMap* gridMap);

    Algorithm(GridMap* gridMap, std::pair<int ,int> start, std::pair<int ,int> goal);

    /**
     * @brief Algorithm destructor. it deletes the pathInMatrix vector. (after use) and all the allocation
     */
    virtual ~Algorithm();

    // getters
    GridMap* getGridMap() const;
    std::pair<int ,int> getStart() const;
    std::pair<int ,int> getGoal() const;
    std::vector<std::pair<int ,int>>* getPath() const;

    // setters
    void setStart(std::pair<int ,int> start);
    void setGoal(std::pair<int ,int> goal);
    void setGridMap(GridMap* gridMap);

    // virtual function that calculate the path from start to goal and setting the pathInMatrix vector.
    virtual void calculate() = 0;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ALGORITHM_H
