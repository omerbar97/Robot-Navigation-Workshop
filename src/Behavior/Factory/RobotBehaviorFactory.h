//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTCOMMANDFACTORY_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTCOMMANDFACTORY_H
#include "../RobotBehavior/RobotBehavior.h"
#include "../RobotBehavior/HallNavigateBehavior.h"
#include "../RobotBehavior/ExitRoomBehavior.h"
#include "../RobotBehavior/EnterRoomBehavior.h"
#include "../../Robot/RobotWrapper.h"
#include <vector>

/**
 * This class is responsible for creating the robot behavior objects.
 * It is a factory class. each object will be created once and will be
 * used by the robot planner.
 */
class RobotBehaviorFactory {
private:

    /**
     * The robot object that will be used by the behaviors.
     */
    RobotWrapper* robot;

    /**
     * The behaviors that were created by the factory. it will holds all the available behaviors.
     */
    std::vector<RobotBehavior*> allBehaviors;

    /**
     * different kind of behaviors that will be created by the factory.
     */
    RobotBehavior* hallNavigateBehavior;
    RobotBehavior* exitRoomBehavior;
    RobotBehavior* enterRoomBehavior;

public:

    /**
     * The constructor of the factory.
     * @param robot the robot object that will be used by the behaviors.
     */
    RobotBehaviorFactory(RobotWrapper* robot, std::pair<double, double> goalPoint);

    /**
     * The destructor of the factory, need to delete all the behaviors that were created.
     * at the end just looping through the vector and delete all the behaviors.
     */
    ~RobotBehaviorFactory();

    /**
     * This method will create the hall navigate behavior.
     * @return RobotBehavior* - the hall navigate behavior.
     */
    RobotBehavior* createHallNavigateBehavior();

    /**
     * This method will create the exit room behavior.
     * @return RobotBehavior* - the exit room behavior.
     */
    RobotBehavior* createExitRoomBehavior();

    /**
     * This method will create the enter room behavior.
     * @return RobotBehavior* - the enter room behavior.
     */
    RobotBehavior* createEnterRoomBehavior();

    /**
     * This method will create all the behaviors that are available. and will append them to the behaviors vector.
     * @return std::vector<RobotBehavior*> - the behaviors that were created.
     */
    std::vector<RobotBehavior*> createAllBehaviors();
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTCOMMANDFACTORY_H
