//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ENTERROOMBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_ENTERROOMBEHAVIOR_H
#include "RobotBehavior.h"
#include "LinearNavigation.h"
#include "../../Resources/Room.h"

using namespace std;
using Point = std::pair<double, double>;

class EnterRoomBehavior : public RobotBehavior {



protected:
    bool avoidObstacles(double &forwardSpeed, double &turnSpeed) override;
    Room* goalRoom;

public:

    /**
     * constructor
     * @param robot the robot wrapper
     * @param goalPoint the point to navigate to
     */
    EnterRoomBehavior(RobotWrapper *robot, Room* goalRoom);
    ~EnterRoomBehavior() override;


    /// Command methods
    int execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ENTERROOMBEHAVIOR_H
