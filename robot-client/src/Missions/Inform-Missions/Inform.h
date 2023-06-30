//
// Created by omer on 6/28/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_INFORM_H
#define ROBOT_NAVIGATION_WORKSHOP_INFORM_H
#include "../Mission.h"
#include "../CalculateTime.h"
#include "../../Behavior/MessageBehavior/VoiceMessageBehavior.h"


class Inform : public Mission {
private:

    Behavior* informBehavior;
    CalculateTime* time;
    Room* currentRoom;
    ChronoTime* chronoTime;


public:
    Inform(CalculateTime* time, Room* currentRoom);
    Inform(ChronoTime* chronoTime, Room* currentRoom);
    ~Inform();

    int doMission() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_INFORM_H
