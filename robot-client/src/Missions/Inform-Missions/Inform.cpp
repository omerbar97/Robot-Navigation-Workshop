//
// Created by omer on 6/28/23.
//

#include "Inform.h"

Inform::Inform(CalculateTime* time, Room* currentRoom) {
    this->time = time;
    this->currentRoom = currentRoom;
}
Inform::Inform(ChronoTime *chronoTime, Room* currentRoom) {
    this->chronoTime = chronoTime;
    this->currentRoom = currentRoom;
}

Inform::~Inform() noexcept {

}

int Inform::doMission() {
    std::string name = currentRoom->getRoomName();
    std::string lowerLettersName;
    for(char c : name) {
        lowerLettersName += tolower(c);
    }

    std::string message;
    // Compare the two time points
    if (this->chronoTime->getMeetingTime() < this->chronoTime->getCurrentTime()) {
        message = "You lost a meeting.";
    } else if (this->chronoTime->getMeetingTime() == this->chronoTime->getCurrentTime()) {
        message = "Meeting is right now.";
        std::cout << "Meeting is right now." << std::endl;
    } else {
        std::chrono::duration<double> duration=  (this->chronoTime->getMeetingTime() - this->chronoTime->getCurrentTime());
        std::string durationString = std::to_string(duration.count()) + " seconds";

        // Convert duration to integral representation
        std::chrono::duration<long long> integralDuration = std::chrono::duration_cast<std::chrono::duration<long long>>(duration);



        // Convert integral duration to hours, minutes, and seconds
        int hours = std::chrono::duration_cast<std::chrono::hours>(integralDuration).count();
        int minutes = std::chrono::duration_cast<std::chrono::minutes>(integralDuration % std::chrono::hours(1)).count();
        int seconds = std::chrono::duration_cast<std::chrono::seconds>(integralDuration % std::chrono::minutes(1)).count();

        message = "Hello " + lowerLettersName + ", please be at the robotic lab at " + this->chronoTime->stringCurrentTime() + "(" +std::to_string(hours)
                + " hours, " + std::to_string(minutes) +
                " minutes, and " + std::to_string(seconds) + " seconds)." ;
    }



//    std::string m = "Hello " + lowerLettersName + ", please be at the robotic lab in " + std::to_string(timeD) + " seconds.";
    this->informBehavior = new VoiceMessageBehavior(message, currentRoom->getRoomName());
    return this->informBehavior->execute();
}
