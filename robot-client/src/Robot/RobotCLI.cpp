//
// Created by ofirhelerman on 6/11/23.
//

#include "RobotCLI.h"

// signal keyboard handler

RobotCLI::RobotCLI(RobotPlanner *robotPlanner) {
    this->robotPlanner = robotPlanner;
}

void RobotCLI::printIntro() {
    std::cout << "Welcome to our Robotics Seminar CLI at Bar-Ilan University!" << std::endl;
    std::cout << std::endl;
    std::cout << "*********************************************" << std::endl;
    std::cout << "*        Robotics Seminar Bar-Ilan          *" << std::endl;
    std::cout << "*                                           *" << std::endl;
    std::cout << "*       © Copyright Shilo Padael,           *" << std::endl;
    std::cout << "*         Omer Bar, Ofir Helerman           *" << std::endl;
    std::cout << "*********************************************" << std::endl;
    std::cout << std::endl;
    std::cout << "This CLI provides access to the Robotics Seminar resources and functionalities." << std::endl;
    std::cout << "Please use the available commands to navigate and interact with the system." << std::endl;
    std::cout << std::endl;
    std::cout << "For assistance, type 'help' or '?' to display the available commands." << std::endl;
    std::cout << std::endl;
}

void RobotCLI::printHelp() {
    std::cout << "Available Commands:" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "start                                        : Start the robot. (Only if stage is running)" << std::endl;
    std::cout << "navigate <current room ID> <roomID> ... <roomID>  : Navigate the robot to the specified rooms.";
    std::cout << std::endl;
    std::cout << "help                                         : Display the available commands and their usage.";
    std::cout << std::endl;
    std::cout << "exit                                         : Exit the CLI.";
    std::cout << std::endl << std::endl;
}

bool RobotCLI::parseCommand(string &input, MissionType &command, vector<string> &args) {
    stringstream ss(input);
    string commandName;
    ss >> commandName;
    if (commandName == "navigate") {
        command = MissionType::NAVIGATION;
    } else if (commandName == "inform") {
        command = MissionType::INFORM;
    } else {
        cout << "command not supported" << endl;
        return false;
    }

    string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }
    return true;
}

void RobotCLI::run() {
    bool isDone = false;
    printIntro();
    while (!isDone) {
        cout << ">> ";
        string input;
        getline(cin, input);
        cout << endl;
        if (input == "exit") {
            isDone = true;
        } else if (input == "help" || input == "?") {
            printHelp();
        } else if (input == "start") {
            this->robotPlanner->initRobot();
            cout << "trying to connect to the robot interface...  ";
            std::cout << '-' << std::flush;
            sleep(1);
            std::cout << "\b\\" << std::flush;
            sleep(1);
            std::cout << "\b|" << std::flush;
            sleep(1);
            std::cout << "\b/" << std::flush;
            sleep(1);
            std::cout << "\b-" << std::flush;
            std::cout << std::endl;
            if(this->robotPlanner->isRobotOnline()) {
                cout << "CONNECTED!" << endl;
            }
            else{
                cout << "FAILED! check if the stage is running and that you are trying to connect to the correct robot ip + port" << endl;
            }

        } else {
            MissionType commandName;
            vector<string> args;
            if (parseCommand(input, commandName, args)) {
                cout << "create plan..." << endl;
                this->robotPlanner->plan(commandName, args);
                cout << "execute plan..." << endl;
                this->robotPlanner->executePlan();
                cout << "done!" << endl;
            }
        }
    }
}

void RobotCLI::setStageThread(std::thread *stageThread) {
    this->stageThread = stageThread;
}
