//
// Created by omer on 5/5/23.
//

#include "RRTStarAlgorithm.h"
RRTStarAlgorithm::RRTStarAlgorithm(GridMap *gridMap) : Algorithm(gridMap) {

}


RRTStarAlgorithm::RRTStarAlgorithm() {

}

RRTStarAlgorithm::~RRTStarAlgorithm() {

}


void RRTStarAlgorithm::calculate() {
    // in case the points are not defined yet dont do anything
    if(this->start.first == -1 || this->start.second == -1 || this->goal.first == -1 || this->goal.second == -1) {
        return;
    }

    // else calculating the path from the starting point to the end
    // the StateSpace is in the gridMap
    ompl::base::StateSpacePtr space(this->gridMap);

    space->as<ompl::base::RealVectorStateSpace>()->setBounds(*this->getGridMap()->getBounds());

    // creating the space information
    ompl::base::SpaceInformationPtr spaceInformation(std::make_shared<ompl::base::SpaceInformation>(space));

    // setting the validity checker
    spaceInformation->setStateValidityChecker(std::make_shared<GridMapValidityChecker>(spaceInformation, this->gridMap));

    // creating the problem definition
    ompl::base::ProblemDefinitionPtr problemDefinition(std::make_shared<ompl::base::ProblemDefinition>(spaceInformation));


    // creating the ScopedState for start and end
    ompl::base::ScopedState<> start(space);
    ompl::base::ScopedState<> goal(space);

    // setting the start and goal
    start[0] = this->start.first;
    start[1] = this->start.second;
    goal[0] = this->goal.first;
    goal[1] = this->goal.second;

    problemDefinition->setStartAndGoalStates(start, goal);

    ompl::geometric::RRTstar* planner = new ompl::geometric::RRTstar(spaceInformation);

    planner->setProblemDefinition(problemDefinition);
    ompl::base::PlannerTerminationCondition ptc = ompl::base::timedPlannerTerminationCondition(10.0);

    ompl::base::PlannerStatus status = planner->solve(ptc);

    if(status == ompl::base::PlannerStatus::EXACT_SOLUTION) {
        ompl::geometric::PathGeometricPtr solutionPath = std::dynamic_pointer_cast<ompl::geometric::PathGeometric>(problemDefinition->getSolutionPath());
        transferPathToVector(solutionPath);

        // deleting memory
        solutionPath.reset();
    } else {
        // failed to find a solution
    }

    delete planner;

}
