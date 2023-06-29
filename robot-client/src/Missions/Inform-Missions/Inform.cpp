//
// Created by omer on 6/28/23.
//

#include "Inform.h"

Inform::Inform(CalculateTime* time, Room* currentRoom) {
    this->time = time;
    this->currentRoom = currentRoom;
}

Inform::~Inform() noexcept {

}

int Inform::doMission() {
    int timeD = time->getTime();
    std::string timeReach = std::to_string(time->getTime());
    std::string name = currentRoom->getRoomName();
    std::string lowerLettersName;
    for(char c : name) {
        lowerLettersName += tolower(c);
    }

    std::string m = "Hello " + lowerLettersName + ", please be at the robotic lab in " + std::to_string(timeD) + " seconds.";
    this->informBehavior = new VoiceMessageBehavior(m, currentRoom->getRoomName());
    return this->informBehavior->execute();
}
