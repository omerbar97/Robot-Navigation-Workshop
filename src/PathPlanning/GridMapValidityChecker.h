//
// Created by omer on 5/10/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_GRIDMAPVALIDITYCHECKER_H
#define ROBOT_NAVIGATION_WORKSHOP_GRIDMAPVALIDITYCHECKER_H
#include <ompl/base/StateValidityChecker.h>
#include "GridMap.h"

class GridMapValidityChecker : public ompl::base::StateValidityChecker {
private:
    GridMap* gridMap;

    // Returns the distance from the given state's position to the
    // boundary of the circular obstacle.
    double clearance(const ompl::base::State* state, int radios) const;

public:
    GridMapValidityChecker(const ompl::base::SpaceInformationPtr& si, GridMap* gridMap);

    bool isValid(const ompl::base::State* state) const override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_GRIDMAPVALIDITYCHECKER_H
