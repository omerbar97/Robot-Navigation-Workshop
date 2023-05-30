//
// Created by omer on 5/10/23.
//

#include "GridMapValidityChecker.h"

GridMapValidityChecker::GridMapValidityChecker(const ompl::base::SpaceInformationPtr &si, GridMap *gridMap)
        : ompl::base::StateValidityChecker(si), gridMap(gridMap) {
}

bool GridMapValidityChecker::isValid(const ompl::base::State *state) const {
    return this->clearance(state, 14);
}

double GridMapValidityChecker::clearance(const ompl::base::State *state, int radius) const {

    const auto *stateType = state->as<ompl::base::RealVectorStateSpace::StateType>();
    // getting the state coordinate
    int x = static_cast<int>(stateType->values[0]);
    int y = static_cast<int>(stateType->values[1]);

    for (int i = x - radius; i <= x + radius; ++i) {
        for (int j = y - radius; j <= y + radius; ++j) {
            // Check if the cell is occupied
            int value = gridMap->getGridMatrix()->at<uchar>(j, i);
            if (value == 255) {
                return false;
            }
        }
    }
    return true;

}
