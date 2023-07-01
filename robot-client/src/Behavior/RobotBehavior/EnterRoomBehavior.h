//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ENTERROOMBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_ENTERROOMBEHAVIOR_H
#include "RobotBehavior.h"
#include "../behaviour-functors/LinearNavigation.h"
#include "../../Resources/Room.h"
#include "../behaviour-functors/RotateRobot.h"


using namespace std;
using Point = std::pair<double, double>;

/**
 * this class responsible for navigating the robot into a room.
 */
class EnterRoomBehavior : public RobotBehavior {

protected:
    // the room the robot is in
    Room* goalRoom;

public:

    /**
     * constructor
     * @param robot the robot wrapper
     * @param goalPoint the point to navigate to
     */
    EnterRoomBehavior(RobotWrapper *robot, Room* goalRoom);
    ~EnterRoomBehavior() override;


    /**
     * this function navigates the robot to the point.
     * @return 0 if the robot reached the point.
     */
    int execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ENTERROOMBEHAVIOR_H
