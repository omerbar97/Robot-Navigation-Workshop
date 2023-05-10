//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTMISSIONFACTORY_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTMISSIONFACTORY_H
#include "../../Robot/RobotWrapper.h"
#include "../../Behavior/RobotBehavior/RobotBehavior.h"
#include "../MessageBehavior/VoiceMessageBehavior.h"
#include "../Mission.h"

class RobotMissionFactory {
private:
    RobotWrapper* robot;

public:

    /**
     * creating the RobotMissionFactory, given the RobotWrapper for the robot that will be used.
     * @param robot - RobotWrapper* - the robot that will be used
     */
    RobotMissionFactory(RobotWrapper* robot);
    ~RobotMissionFactory();

    /**
     * this will create a mission called navigation which will calculate the shortestPath from the robot current
     * location to the stagePoint and will navigate the robot to that point. (when executed)
     * @param behavior - the behavior that will be executed when the mission is executed, for example Navigation in Hall
     * @param stagePointToNavigate - the point that the robot will navigate to
     * @return Mission* - the mission that was created
     */
    Mission* createNavigationMission(RobotBehavior* behavior, std::vector<std::pair<double, double>> path);

    /**
     * this will create a mission that will message the messageTo with the message, using the behavior.
     * the behavior can be implemented in different ways, for example, sending a voice message, or a text message.
     * @param behavior - the behavior that will be executed when the mission is executed, for example VoiceMessage
     * @param message - the message that will be sent
     * @param messageTo - the attachment of the message (name of professor...)
     * @return
     */
    Mission* createMessageMission(MessageBehavior* behavior, std::string message, std::string messageTo);


};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTMISSIONFACTORY_H
