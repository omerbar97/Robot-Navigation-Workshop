//
// Created by ofirhelerman on 6/11/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTCLI_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTCLI_H

#include <iostream>
#include <sstream>
#include <vector>
#include "RobotPlanner.h"

class RobotCLI {
private:
    RobotPlanner* robotPlanner;
    void printIntro();
    void printHelp();
    bool parseCommand(string& input, MissionType& command, vector<string>& args);


public:
    explicit RobotCLI(RobotPlanner *robotPlanner);
    void run();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTCLI_H
