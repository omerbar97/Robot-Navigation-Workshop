//
// Created by omer on 5/9/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_MESSAGEBEHAVIOR_H
#define ROBOT_NAVIGATION_WORKSHOP_MESSAGEBEHAVIOR_H
#include "../Behavior.h"
#include "string"

/**
 * this interface is for sending a message to a specific person. (string)
 */
class MessageBehavior : public Behavior {
private:

    /**
     * all the fields are for the message.
     */
    std::string message; // can be general format
    std::string time; // the time of the message
    std::string messageTo; // who is sending the message to

public:

    /**
     * constructor for the message behavior.
     * @param message the message to send.
     * @param messageTo the name of the person to send the message to.
     */
    MessageBehavior(std::string message, std::string messageTo);
    void execute() = 0;
};

#endif //ROBOT_NAVIGATION_WORKSHOP_MESSAGEBEHAVIOR_H
