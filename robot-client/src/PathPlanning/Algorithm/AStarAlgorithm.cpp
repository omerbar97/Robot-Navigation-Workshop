//
// Created by omer on 5/5/23.
//

#include "AStarAlgorithm.h"

AStarAlgorithm::AStarAlgorithm(GridMap *gridMap) : Algorithm(gridMap) {

}

void AStarAlgorithm::calculate() {
    // in case the points are not defined yet dont do anything
    if(this->start.first == -1 || this->start.second == -1 || this->goal.first == -1 || this->goal.second == -1) {
        return;
    }

    // else calculating the path from the starting point to the end
    // the space information is in the gridMap
    ompl::base::StateSpacePtr space(this->gridMap);
    ompl::geometric::SimpleSetup setup(space);

    // creating the ScopedState for start and end
    ompl::base::ScopedState<> start(space);
    ompl::base::ScopedState<> goal(space);

    // setting the start and goal
    start[0] = this->start.first;
    start[1] = this->start.second;
    goal[0] = this->goal.first;
    goal[1] = this->goal.second;

    setup.setStartAndGoalStates(start, goal);

    ompl::geometric::AStar planner(setup.getSpaceInformation());



}
