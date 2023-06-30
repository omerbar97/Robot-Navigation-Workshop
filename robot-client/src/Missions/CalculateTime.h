//
// Created by omer on 6/28/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
#define ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
#include "Mission.h"
#include "../Resources/ChronoTime.h"

class CalculateTime : public Mission {
private:
    std::vector<std::pair<double, double>>* path;
    double robotSpeed;
    double time;
    ChronoTime* chronoTime;

public:

    ChronoTime *getChronoTime() const;

    void setChronoTime(ChronoTime *chronoTime);

    CalculateTime(std::vector<std::pair<double, double>>* path, double robotSpeed);
    CalculateTime(ChronoTime *chronoTime);
    ~CalculateTime();

    int doMission() override;

    double getTime();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_CALCULATETIME_H
