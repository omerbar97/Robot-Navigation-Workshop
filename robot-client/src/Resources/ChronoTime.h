//
// Created by shilopadael on 6/30/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_CHRONOTIME_H
#define ROBOT_NAVIGATION_WORKSHOP_CHRONOTIME_H

#include <iostream>
#include <chrono>
#include <ctime>

class ChronoTime {
private:
    std::chrono::system_clock::time_point meetingTime;
    std::string convertTimeToString(const std::chrono::system_clock::time_point& timePoint);


public:
    ChronoTime();
    const std::chrono::system_clock::time_point& getMeetingTime() const;
    void setMeetingTime(const std::chrono::system_clock::time_point& meetingTime);
    std::string stringCurrentTime();

    // Get current time
    std::chrono::system_clock::time_point getCurrentTime();
};

#endif // ROBOT_NAVIGATION_WORKSHOP_CHRONOTIME_H
