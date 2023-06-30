//
// Created by shilopadael on 6/30/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTPATHPRODUCER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTPATHPRODUCER_H

#include <vector>
#include "../Resources/Room.h"
using Point = std::pair<double, double>;
using MissionPathList = std::vector<std::vector<Point>>;
class RobotPathProducer {


private:
    MissionPathList *path;




public:
    RobotPathProducer();

    ~RobotPathProducer() = default;
    MissionPathList getPath();
    void setPath(MissionPathList path);



};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTPATHPRODUCER_H
