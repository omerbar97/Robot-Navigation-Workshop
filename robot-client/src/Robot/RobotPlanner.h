//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
#include <vector>
#include <queue>
#include <mutex>
#include <chrono>
#include <ctime>
#include "../Resources/Room.h"
#include "../Resources/RoomsContainer.h"
#include "RobotWrapper.h"
#include "../PathPlanning/Route.h"
#include "../Resources/MapGenerator.h"
#include "../PathPlanning/Algorithm/RRTStarAlgorithm.h"
#include "../Behavior/Behavior.h"
#include "../Missions/Mission.h"
#include "../Missions/CalculateTime.h"
#include "../Missions/navigation-missions/R2R.h"
#include <boost/bind/bind.hpp>
#include "../Missions/navigation-missions/R2Exit.h"
#include <thread>
#include <condition_variable>
#include <unordered_set>
#include "../Resources/ChronoTime.h"
#include "../Missions/Inform-Missions/Inform.h"

using namespace boost::placeholders;

struct arrangedRoom{
    Room* room;
    double distance;
};

using namespace std;
class RobotPlanner {
private:
    bool isInPlan;
    RoomsContainer* roomsContainer;
    RobotWrapper *robotWrapper;
    queue<Mission*> currentPlan;
    MapGenerator* map;
    std::thread *robotTimeoutThread;
    std::mutex robotLock;
    std::mutex missionLock;
    void planInformMission(const vector<string>& roomsIDs);
    void planNavigationMission(vector<string>& roomsIDs);
    std::vector<std::string> salesManProblem(const vector<string>& roomsIDs, Point currentLocation);
    std::vector<std::string> removeDuplicates(std::vector<std::string>& vec);
    void finishGracefully(queue<Mission *>& queue);
    ChronoTime* chronoTime;
public:


    RobotPlanner(const string& roomConfigPath, RobotWrapper* robotWrapper, MapGenerator* map);
    ~RobotPlanner();
    void plan(const MissionType& mission, vector<string>& parameters);
    void setPlanFromString(const string& plan);
    int executePlan();
    bool isRobotOnline();
    RobotWrapper* getRobotWrapper();
    void initRobot();
    bool isRobotInPlan();
    condition_variable cv;
    void robotTimeout();
    ChronoTime *getChronoTime() const;
    void setRobotWrapper(RobotWrapper* robot);

    void setChronoTime(ChronoTime *chronoTime);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
