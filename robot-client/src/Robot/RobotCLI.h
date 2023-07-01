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

    /**
     * print the welcome screen
     */
    void printIntro();

    /**
     * print the help screen
     */
    void printHelp();

    /**
     * passing command when executing a new command to the robot.
     */
    bool parseCommand(string& input, MissionType& command, vector<string>& args);

    /**
     * printing the robot information
     */
    void printShowRobotInfo();

    /**
     * the function set new settings to the robot, speed, rotation, optimized...
     * @param settings
     */
    void setSettings(const string& settings);

    /**
     * starting the robot and setting a new meeting time.
     * @param input
     */
    void doStartCommand(string& input);


public:

    /**
     * the robotCLI constructor
     * @param robotPlanner - RobotPlanner class
     */
    explicit RobotCLI(RobotPlanner *robotPlanner);

    /**
     * the class destructor
     */
    ~RobotCLI();

    /**
     * starting the CLI loop.
     */
    void run();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTCLI_H
