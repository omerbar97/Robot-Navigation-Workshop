//
// Created by omer on 5/9/23.
//

#include "VoiceMessageBehavior.h"

int VoiceMessageBehavior::execute() {

}

VoiceMessageBehavior::VoiceMessageBehavior(std::string message, std::string messageTo) : MessageBehavior(message, messageTo) {
    // generating the voice message
    std::string command = "espeak -ven+f3 -k2 -s130 --stdout \"" + message + "\" | aplay";
    system(command.c_str());
}

VoiceMessageBehavior::~VoiceMessageBehavior() {

}