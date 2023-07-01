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
    ChronoTime* chronoTime;

    /**
     * given room id strings "9 1 3 2" creating a navigation mission if the room id is valid.
     * @param roomsIDs
     */
    void planNavigationMission(vector<string>& roomsIDs);

    /**
     * given vector of strings of room id creating an optimized path using the salesManProblem algorithm
     * for more information: https://en.wikipedia.org/wiki/Travelling_salesman_problem
     * @param roomsIDs - vector of strings
     * @param currentLocation - the current robot location
     * @return a new optimized vector structure.
     */
    std::vector<std::string> salesManProblem(const vector<string>& roomsIDs, Point currentLocation);

    /**
     * removing the duplicates rooms in a given vector of strings.
     * @param vec - vector of strings.
     * @return a new vector of string without duplicates
     */
    std::vector<std::string> removeDuplicates(std::vector<std::string>& vec);

    /**
     * finishing the execution gracefully
     * @param queue - queue of Mission*
     */
    void finishGracefully(queue<Mission *>& queue);

public:

    /**
     * creating the robot-planner, handle to navigate the robot around.
     * @param roomConfigPath - the room config path.
     * @param robotWrapper - the robot it self
     * @param map - the map generator of the given map.
     */
    RobotPlanner(const string& roomConfigPath, RobotWrapper* robotWrapper, MapGenerator* map);

    /**
     * deleting the robot planner class
     */
    ~RobotPlanner();

    /**
     * planning a new mission by the given parameter.
     * @param mission - enum MissionType
     * @param parameters - vector of strings
     */
    void plan(const MissionType& mission, vector<string>& parameters);

    /**
     * given a string of rooms id, breaking it down to vector of strings.
     * @param plan
     */
    void setPlanFromString(const string& plan);

    /**
     * executing the plan of the current queue.
     * @return 0 if succeed, otherwise return error code.
     */
    int executePlan();

    /**
     * returning true if the robot is online (connected to the stage) and false otherwise.
     * @return boolean
     */
    bool isRobotOnline();

    /**
     * getter for the robot-wrapper instance.
     * @return
     */
    RobotWrapper* getRobotWrapper();

    /**
     * starting the robot-wrapper, connection the robot it self.
     */
    void initRobot();

    /**
     * returning true if the robot is currently in a movement.
     * @return
     */
    bool isRobotInPlan();

    /**
     * function that is executing in a different thread and every 8 seconds send Read command to the stage to avoid timeout from the stage process.
     */
    void robotTimeout();

    /**
     * getting the ChronoTime
     * @return
     */
    ChronoTime *getChronoTime() const;

    /**
     * setter for the robot-wrapper.
     * @param robot
     */
    void setRobotWrapper(RobotWrapper* robot);

    /**
     * setter for the chrono-time.
     * @param chronoTime
     */
    void setChronoTime(ChronoTime *chronoTime);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTPLANNER_H
