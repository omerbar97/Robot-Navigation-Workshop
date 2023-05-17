//
// Created by omer on 5/5/23.
//

#include "Algorithm.h"
Algorithm::Algorithm() {
    this->gridMap == nullptr;
    this->pathInMatrix = nullptr;
    // undefined start and goal
    this->start.first = -1;
    this->start.second = -1;
    this->goal.first = -1;
    this->goal.second = -1;

}


Algorithm::Algorithm(GridMap *gridMap, std::pair<int, int> start, std::pair<int, int> goal) {
    this->gridMap = gridMap;
    this->start = start;
    this->goal = goal;
    this->pathInMatrix = nullptr;
}

Algorithm::Algorithm(GridMap *gridMap) {
    this->gridMap = gridMap;

    // undefined start and goal
    this->start.first = -1;
    this->start.second = -1;
    this->goal.first = -1;
    this->goal.second = -1;
}

GridMap *Algorithm::getGridMap() const {
    return this->gridMap;
}

std::pair<int, int> Algorithm::getStart() const {
    return this->start;
}

std::pair<int, int> Algorithm::getGoal() const {
    return this->goal;
}

std::vector<std::pair<int, int>> *Algorithm::getPath() const {
    return this->pathInMatrix;
}

void Algorithm::setStart(std::pair<int, int> start) {
    this->start = start;
}

void Algorithm::setGoal(std::pair<int, int> goal) {
    this->goal = goal;
}

void Algorithm::setGridMap(GridMap *gridMap) {
    this->gridMap = gridMap;
}

void Algorithm::transferPathToVector(ompl::geometric::PathGeometricPtr solutionPath) {
    this->pathInMatrix = new std::vector<std::pair<int, int>>;

    // iterating through each state and adding a new pair to it
    const std::vector<ompl::base::State*>& states = solutionPath->getStates();

    for(const auto& state : states) {
        const auto* stateType = state->as<ompl::base::RealVectorStateSpace::StateType>();
        int x = static_cast<int>(stateType->values[0]);
        int y = static_cast<int>(stateType->values[1]);
        this->pathInMatrix->emplace_back(x, y);
    }
}

Algorithm::~Algorithm() {
    if(this->pathInMatrix != nullptr) {
        delete this->pathInMatrix;
    }
}

