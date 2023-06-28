//
// Created by shilopadael on 6/14/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_R2R_H
#define ROBOT_NAVIGATION_WORKSHOP_R2R_H

#include "../Mission.h"
#include "../../Behavior/RobotBehavior/EnterRoomBehavior.h"
#include "../../Behavior/RobotBehavior/HallNavigateBehavior.h"
#include "../../Behavior/RobotBehavior/ExitRoomBehavior.h"
#include "../../PathPlanning/Algorithm/Algorithm.h"
#include "../../Resources/MapGenerator.h"
#include <boost/bind/bind.hpp>
#include "../../PathPlanning/Route.h"
#include "../../Robot/Colors.h"

using namespace boost::placeholders;


using namespace std;
using Point = std::pair<double, double>;
class R2R : public Mission {
private:

    Route* route;
    RobotWrapper* robot;
    vector<Behavior*> tasks;
    Algorithm* algorithm;
    std::vector<std::pair<double, double>> path;


public:
    R2R(Room* roomSource, Room* roomDest, RobotWrapper* robot, Algorithm* algorithm, MapGenerator* mapGenerator);

    ~R2R();

    std::vector<std::pair<double, double>> getPath();

    int doMission() override;



};



#endif //ROBOT_NAVIGATION_WORKSHOP_R2R_H
