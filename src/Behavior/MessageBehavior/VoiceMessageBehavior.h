//
// Created by omer on 5/9/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_VOICEMESSAGEBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_VOICEMESSAGEBEHAVIOR_H
#include "MessageBehavior.h"

/**
 * this class is responsible for sending voice messages from the computer using an AI generator voice and output voice
 * stream. the message is kind of a mission that is seperated from the robot's mission. but is part of it.
 */
class VoiceMessageBehavior : public MessageBehavior{
public:

    VoiceMessageBehavior(std::string message, std::string messageTo);
    void execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_VOICEMESSAGEBEHAVIOR_H
