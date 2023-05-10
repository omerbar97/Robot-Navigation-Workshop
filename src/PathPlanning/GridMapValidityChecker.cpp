//
// Created by omer on 5/10/23.
//

#include "GridMapValidityChecker.h"

GridMapValidityChecker::GridMapValidityChecker(const ompl::base::SpaceInformationPtr &si, GridMap *gridMap)
                        : ompl::base::StateValidityChecker(si), gridMap(gridMap) {
}

bool GridMapValidityChecker::isValid(const ompl::base::State *state) const {
    const auto *stateType = state->as<ompl::base::RealVectorStateSpace::StateType>();
    int x = static_cast<int>(stateType->values[0]);
    int y = static_cast<int>(stateType->values[1]);

    if (x < 0 || x >= gridMap->getWidth() || y < 0 || y >= gridMap->getHeight())
        return false; // State is out of bounds

    // Retrieve the value from the grid matrix at the specified coordinates
    int value = gridMap->getGridMatrix()->at<uchar>(y, x);

    // Check if the cell is occupied
    if (value == 255)
        return false;

    return true;
}