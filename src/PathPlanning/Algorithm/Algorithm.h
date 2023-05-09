//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ALGORITHM_H
#define ROBOT_NAVIGATION_WORKSHOP_ALGORITHM_H
#include <ompl/base/SpaceInformation.h>
#include <ompl/base/Planner.h>
#include <ompl/geometric/SimpleSetup.h>
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
    GridMap* gridMap;
    std::shared_ptr<ompl::base::Planner> planner;
    std::pair<int ,int> start;
    std::pair<int ,int> goal;
    std::vector<std::pair<int ,int>> pathInMatrix;

    void transferPathToVector(ompl::geometric::PathGeometric* solutionPath);

public:

    Algorithm(GridMap* gridMap);
    virtual ~Algorithm();

    // getters
    GridMap* getGridMap() const;
    std::pair<int ,int> getStart() const;
    std::pair<int ,int> getGoal() const;
    std::vector<std::pair<int ,int>> getPath() const;

    // setters
    void setStart(std::pair<int ,int> start);
    void setGoal(std::pair<int ,int> goal);
    void setGridMap(GridMap* gridMap);

    // virtual function that calculate teh path from start to goal and setting the pathInMatrix vector.
    virtual void calculate() = 0;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ALGORITHM_H
