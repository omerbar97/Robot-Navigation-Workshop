//
// Created by omer on 6/28/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
#define ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
#include "Mission.h"
#include "../Resources/ChronoTime.h"

/**
 * This class is responsible for calculating the time left for the meeting.
 */
class CalculateTime : public Mission {
private:
    std::vector<std::pair<double, double>>* path;
    double time;
    ChronoTime* chronoTime;

public:

    /**
     * function: getChronoTime
     * -----------------------
     * @return chronoTime
     */
    ChronoTime *getChronoTime() const;

    /**
     * function: setChronoTime
     * -----------------------
     * @param chronoTime the chronoTime object
     */
    void setChronoTime(ChronoTime *chronoTime);

    /**
     * constructor
     * @param chronoTime - the chronoTime object
     */
    CalculateTime(ChronoTime *chronoTime);
    //destructor
    ~CalculateTime();

    int doMission() override;

    /**
     * function: getTime
     * -----------------------
     * getter for the time
     * @return time
     */
    double getTime();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
