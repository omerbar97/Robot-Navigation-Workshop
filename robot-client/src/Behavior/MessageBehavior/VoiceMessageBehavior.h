//
// Created by omer on 5/9/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_VOICEMESSAGEBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_VOICEMESSAGEBEHAVIOR_H
#include "MessageBehavior.h"
#include <iostream>
#include "../../Robot/Colors.h"
#include <utility>

/**
 * this class is responsible for sending voice messages from the computer using an AI generator voice and output voice
 * stream. the message is kind of a mission that is seperated from the robot's mission. but is part of it.
 */
class VoiceMessageBehavior : public MessageBehavior{
public:

    /**
     * constructor for the voice message behavior.
     * @param message the message to send.
     * @param messageTo the name of the person to send the message to.
     */
    VoiceMessageBehavior(const std::string& message, std::string messageTo);
    //destructor
    ~VoiceMessageBehavior() override;
    /**
     * this function is responsible for sending the message.
     * @return 0 if the message was sent successfully.
     */
    int execute() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_VOICEMESSAGEBEHAVIOR_H
