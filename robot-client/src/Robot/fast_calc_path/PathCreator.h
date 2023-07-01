//
// Created by ofirhelerman on 6/30/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_PATHCREATOR_H
#define ROBOT_NAVIGATION_WORKSHOP_PATHCREATOR_H

#include "../../Resources/RoomsContainer.h"
#include "../../Resources/MapGenerator.h"

#define RED "\e[0;31m"
#define COLOR_RESET "\e[0m"

using Point = std::pair<double, double>;
using MissionPathList = std::vector<std::vector<Point>>;
using MissionData = std::pair<int, int>;
using MissionDataList = std::vector<MissionData>;

class PathCreator {
private:
    Point startPoint;
    int startRoomID;
    Point goalPoint;
    int goalRoomID;
    MapGenerator *map;
    MissionPathList *path;
    int cellID;

public:
    PathCreator(Point startPoint, int startRoomID, Point endPoint,int goalRoomID, MapGenerator *map,
                MissionPathList *path, int cellID);
    void operator()();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_PATHCREATOR_H
