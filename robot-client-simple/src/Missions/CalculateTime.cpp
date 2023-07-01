//
// Created by omer on 6/28/23.
//

#include "CalculateTime.h"

CalculateTime::CalculateTime(ChronoTime* chronoTime) {
    this->chronoTime = chronoTime;
}
int CalculateTime::doMission() {

}

double CalculateTime::getTime() {
    return this->time;
}

CalculateTime::~CalculateTime() {

}

ChronoTime *CalculateTime::getChronoTime() const {
    return chronoTime;
}

void CalculateTime::setChronoTime(ChronoTime *chronoTime) {
    CalculateTime::chronoTime = chronoTime;
}

