//
// Created by omer on 6/28/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_INFORM_H
#define ROBOT_NAVIGATION_WORKSHOP_INFORM_H
#include "../Mission.h"
#include "../CalculateTime.h"
#include "../../Behavior/MessageBehavior/VoiceMessageBehavior.h"

/**
 * This class is responsible for informing the person in the room about the meeting it's part of, and the time left
 * for the meeting.
 */
class Inform : public Mission {
private:

    Behavior* informBehavior;
    Room* currentRoom;
    ChronoTime* chronoTime;


public:
    /**
     * constructor
     * @param chronoTime the chronoTime object
     * @param currentRoom the room the robot is in
     */
    Inform(ChronoTime* chronoTime, Room* currentRoom);
    //destructor
    ~Inform();

    int doMission() override;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_INFORM_H
