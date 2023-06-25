//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
#include <vector>
#include <queue>
#include <mutex>
#include "../Resources/Room.h"
#include "../Resources/RoomsContainer.h"
#include "RobotWrapper.h"
#include "../PathPlanning/Route.h"
#include "../Resources/MapGenerator.h"
#include "../PathPlanning/Algorithm/RRTStarAlgorithm.h"
#include "../Behavior/Factory/RobotBehaviorFactory.h"
#include "../Behavior/Behavior.h"
#include "../Missions/Mission.h"
#include "../Missions/navigation-missions/R2R.h"
#include "../Missions/factories/nav-mission-factory/NavigationMissionsFactory.h"


using namespace std;
class RobotPlanner {
private:
    bool isInPlan;
    RoomsContainer* roomsContainer;
    RobotWrapper *robotWrapper;
    queue<Mission*> currentPlan;
    MapGenerator* map;
    std::mutex mutex;
    void planInformMission(const vector<string>& roomsIDs);
    void planNavigationMission(const vector<string>& roomsIDs);


public:
    RobotPlanner(const string& roomConfigPath, RobotWrapper* robotWrapper, MapGenerator* map);
    ~RobotPlanner();
    void plan(const MissionType& mission, const vector<string>& parameters);
    void setPlanFromString(const string& plan);
    int executePlan();
    bool isRobotOnline();
    RobotWrapper* getRobotWrapper();
    void initRobot();
    bool isRobotInPlan();



};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
