//
// Created by ofirhelerman on 6/11/23.
//

#include "RobotCLI.h"

// signal keyboard handler

RobotCLI::RobotCLI(RobotPlanner *robotPlanner) {
    this->robotPlanner = robotPlanner;
    this->robotInfo.groundSpeed = 0.1;
    this->robotInfo.rotationSpeed = 0.03;
    this->robotInfo.robotCurrentYawInDegree = 0;
    this->robotInfo.optimizedPath = true;
    this->robotInfo.ip = "localhost";
    this->robotInfo.port = 6665;
}

void RobotCLI::printIntro() {
    std::cout << "Welcome to our Robotics Seminar CLI at Bar-Ilan University!" << std::endl;
    std::cout << std::endl;
    std::cout << BLU << "*********************************************" << std::endl;
    std::cout << "*        Robotics Seminar Bar-Ilan          *" << std::endl;
    std::cout << "*                                           *" << std::endl;
    std::cout << "*       © Copyright Shilo Padael,           *" << std::endl;
    std::cout << "*         Omer Bar, Ofir Helerman           *" << std::endl;
    std::cout << "*********************************************" << RESET_COLOR << std::endl;
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
    std::cout << "info                                         : Display the robot information variables" << std::endl;
    std::cout << "set ground                                   : setting the robot ground speed (default 0.1)" << std::endl;
    std::cout << "set rotation                                 : setting the robot rotation speed (default 0.03)" << std::endl;
    std::cout << "set opt                                      : setting the robot optimized calculate path (default True)" << std::endl;
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
            cout<<"How long until the meeting? (in seconds)"<<endl;
            cout << ">> ";
            getline(cin, input);

            while (std::stoi(input) == 0) {
                cout<<"Please enter a valid number"<<endl;
                cout << ">> ";
                getline(cin, input);
            }
            int time = std::stoi(input);

            // Get the current system time
            std::chrono::system_clock::time_point now = this->robotPlanner->getChronoTime()->getCurrentTime();

            // Add the time until the meeting and set meeting time
            now += std::chrono::seconds(time);
            this->robotPlanner->getChronoTime()->setMeetingTime(now);

            // init robot planner
            if(this->robotPlanner->isRobotOnline()) {
                // robot already online
                cout << CYNB << "robot already online" << RESET_COLOR << endl;
            } else {
                this->robotPlanner->initRobot();
                cout << RED << "trying to connect to the robot interface... " ;
                std::cout << '-' << std::flush;
                usleep(300000);
                std::cout << "\b\\" << std::flush;
                usleep(300000);
                std::cout << "\b|" << std::flush;
                usleep(300000);
                std::cout << "\b/" << std::flush;
                usleep(300000);
                std::cout << "\b-" << std::flush;
                std::cout << RESET_COLOR << std::endl;
                if(this->robotPlanner->isRobotOnline()) {
                    cout << GRNB << "CONNECTED!" << RESET_COLOR << endl;
                    this->robotPlanner->getRobotWrapper()->setRobotSpeed(this->robotInfo.groundSpeed);
                    this->robotPlanner->getRobotWrapper()->setRobotTurnSpeed(this->robotInfo.rotationSpeed);
                    this->robotPlanner->getRobotWrapper()->setFastTravel(this->robotInfo.optimizedPath);
                    this->robotPlanner->getRobotWrapper()->setStartingDegree(this->robotInfo.robotCurrentYawInDegree);

                }
                else{
                    cout << REDB << "FAILED! check if the stage is running and that you are trying to connect to the correct robot ip + port" << RESET_COLOR << endl;
                }
            }
            cout << YEL << "new time meeting was set!" << RESET_COLOR << endl;

        } else if(input == "info") {
            printShowRobotInfo();
        }  else if (input == "set yaw" || input == "set ground" || input == "set rotation" || input == "set opt") {
            setSettings(input);
        }
        else {
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

void RobotCLI::printShowRobotInfo() {
    // printing the robot detail settings
    cout << CYN << "The robot starting yaw is the robot degree when first initialized based on the given map\n"
                   "the map is an x,y coordinate system where the 90 degree is at the y axios (front)\n"
                   "and the 0 degree is on the x axios (right, if looking at the front)" << RESET_COLOR << "\n";
    cout << BLU << "                 Y axios 90 degree                \n"
                   "                        ^                         \n"
                   "                        |                         \n"
                   "                        |                         \n"
                   "                        |                         \n"
                   "                        |                         \n"
                   "            -------------------------> X axios 0 degree\n"
                   "                        |                         \n"
                   "                        |                         \n"
                   "                        |                         \n"
                   "                        |                         \n"
                   "                        |                         \n" << RESET_COLOR;
    cout << YEL << "Robot starting Yaw: " << RESET_COLOR << GRN << this->robotInfo.robotCurrentYawInDegree << RESET_COLOR << endl;
    cout << YEL << "Robot ground speed: " << RESET_COLOR << GRN << this->robotInfo.groundSpeed << RESET_COLOR << endl;
    cout << YEL << "Robot rotation speed: " << RESET_COLOR << GRN << this->robotInfo.rotationSpeed << RESET_COLOR << endl;
    if(this->robotInfo.optimizedPath) {
        cout << YEL << "Optimized path enable: " << RESET_COLOR << GRN << "True" << RESET_COLOR << endl;
    } else {
        cout << YEL << "Optimized path enable: " << RESET_COLOR << GRN << "False" << RESET_COLOR << endl;
    }
}

void RobotCLI::setSettings(const string &settings) {
    if (settings == "set ground") {
        // setting the ground speed
        cout << "enter the ground speed (default 0.1, 1 meter per second): ";
        string input;
        getline(cin, input);
        double groundSpeed;
        try {
            groundSpeed = stod(input);
        } catch (exception &e) {
            cout << RED << "invalid input, setting to default: 0.1" << RESET_COLOR << endl;
            this->robotInfo.groundSpeed = 0.1;
            this->robotPlanner->getRobotWrapper()->setRobotSpeed(0.1);
            return;
        }
        this->robotInfo.groundSpeed = groundSpeed;
        this->robotPlanner->getRobotWrapper()->setRobotSpeed(groundSpeed);
        cout << YEL << "ground speed set to: " << groundSpeed << RESET_COLOR << endl;

    } else if (settings == "set rotation") {
        // setting the rotation speed
        cout << "enter the rotation speed (default 0.03 radian per second): ";
        string input;
        getline(cin, input);
        double rotationSpeed;
        try {
            rotationSpeed = stod(input);
        } catch (exception &e) {
            cout << RED << "invalid input, setting to default: 0.03" << RESET_COLOR << endl;
            this->robotInfo.rotationSpeed = 0.03;
            this->robotPlanner->getRobotWrapper()->setRobotTurnSpeed(0.03);
            return;
        }
        this->robotInfo.rotationSpeed = rotationSpeed;
        this->robotPlanner->getRobotWrapper()->setRobotTurnSpeed(rotationSpeed);
        cout << YEL << "rotation speed set to: " << rotationSpeed << RESET_COLOR << endl;

    } else if (settings == "set opt") {
        // setting the rotation speed
        cout << "enter the optimized path (default true): ";
        string input;
        getline(cin, input);
        bool opt;
        if(input == "true") {
            opt = true;
        } else if(input == "false") {
            opt = false;
        } else {
            cout << RED << "invalid input, setting to default: true" << RESET_COLOR << endl;
            this->robotInfo.optimizedPath = true;
            this->robotPlanner->getRobotWrapper()->setFastTravel(true);
            return;
        }
        this->robotInfo.optimizedPath = opt;
        this->robotPlanner->getRobotWrapper()->setFastTravel(opt);
        if(opt) {
            cout << YEL << "optimized path set to: " << RESET_COLOR << GRNB << "True" << RESET_COLOR << endl;
        } else {
            cout << YEL << "optimized path set to: " << RESET_COLOR << REDB << "False" << RESET_COLOR << endl;
        }
    }  else {
        cout << RED << "setting not found" << RESET_COLOR << endl;
    }

}