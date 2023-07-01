//
// Created by ofirhelerman on 6/11/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTCLI_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTCLI_H

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>
#include "RobotPlanner.h"
#include <thread>
#include <boost/bind/bind.hpp>
#include "Colors.h"
using namespace boost::placeholders;

struct robotInformation {
    double groundSpeed;
    double rotationSpeed;
    double robotCurrentYawInDegree;
    std::string ip;
    int port;
    bool optimizedPath;

};

class RobotCLI {
private:
    robotInformation robotInfo;
    RobotPlanner* robotPlanner;
    std::thread* stageThread;
    void printIntro();
    void printHelp();
    bool parseCommand(string& input, MissionType& command, vector<string>& args);
    void printShowRobotInfo();
    void setSettings(const string& settings);
    void doStartCommand(string& input);
    void exitCLI();


public:

    void setStageThread(std::thread* stageThread);
    explicit RobotCLI(RobotPlanner *robotPlanner);
    ~RobotCLI();
    void run();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTCLI_H
