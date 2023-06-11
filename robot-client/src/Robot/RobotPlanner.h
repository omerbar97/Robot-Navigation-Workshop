//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
#include <vector>
#include "../Resources/Room.h"
#include "../Resources/RoomsContainer.h"
#include "RobotWrapper.h"
#include "../PathPlanning/Route.h"
#include "../Resources/MapGenerator.h"
#include "../PathPlanning/Algorithm/RRTStarAlgorithm.h"
#include "../Behavior/Factory/RobotBehaviorFactory.h"
#include "../Behavior/Behavior.h"
#include "../Behavior/Mission.h"


using namespace std;
class RobotPlanner {
private:
    RoomsContainer* roomsContainer;
    RobotWrapper *robotWrapper;
    Route* route;
    MapGenerator* mapGenerator;
    RobotBehaviorFactory* robotBehaviorFactory;
    vector<Behavior*> currentPlan;
    void planInformMission(const vector<string>& roomsIDs);
    void planNavigationMission(const vector<string>& roomsIDs);

//    void goToPoint(std::pair<double, double> point);

public:
    RobotPlanner(const string& roomConfigPath, RobotWrapper* robotWrapper, MapGenerator* mapGenerator);
    ~RobotPlanner();
    void plan(const MissionType& mission, const vector<string>& parameters);
    int executePlan();



};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
