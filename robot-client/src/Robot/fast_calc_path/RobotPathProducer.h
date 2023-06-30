//
// Created by shilopadael on 6/30/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTPATHPRODUCER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTPATHPRODUCER_H

#include <vector>
#include <thread>

#include "../../Resources/Room.h"
#include "../../Resources/RoomsContainer.h"
#include "../../Resources/MapGenerator.h"
#include "PathCreator.h"

using Point = std::pair<double, double>;
using MissionPathList = std::vector<std::vector<Point>>;
using MissionData = std::pair<int, int>;
using MissionDataList = std::vector<MissionData>;
class RobotPathProducer {


private:
    MissionPathList *path;
    MissionDataList *data;
    RoomsContainer* roomsContainer;
    MapGenerator *map;

public:
    RobotPathProducer(MissionDataList *data, RoomsContainer* roomsContainer, MapGenerator *map);

    ~RobotPathProducer() = default;
    MissionPathList getPath();
    void setPath(MissionPathList path);

    MissionPathList* createPaths();



};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTPATHPRODUCER_H
