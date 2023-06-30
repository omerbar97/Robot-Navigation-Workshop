//
// Created by omer on 5/9/23.
//

#include "VoiceMessageBehavior.h"

#include <utility>

int VoiceMessageBehavior::execute() {
    // generating the voice message
//    std::string command = "espeak -ven+f3 -k2 -s130 --stdout \"" + message + "\" | aplay";
    std::string command = "espeak -v english_rp -s120 \"" + message + "\"";
    std::cout << CYNB << "Sending message to: " << RESET_COLOR << YELB << messageTo << RESET_COLOR << std::endl;
    std::cout << CYNB << "Content: " << RESET_COLOR << YELB << message << RESET_COLOR << std::endl;
    system(command.c_str());
    return 0;
}

VoiceMessageBehavior::VoiceMessageBehavior(const std::string& message, std::string messageTo) : MessageBehavior(message, std::move(messageTo)) {

}

VoiceMessageBehavior::~VoiceMessageBehavior() {

}