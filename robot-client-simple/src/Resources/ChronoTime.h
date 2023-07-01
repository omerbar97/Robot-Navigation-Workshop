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

    /**
     * converting the given time to a string format.
     * @param timePoint - std::chrono::system_clock::time_point
     * @return a new string representation of the given time.
     */
    std::string convertTimeToString(const std::chrono::system_clock::time_point& timePoint);


public:
    /**
     * Constructor for the ChronoTime class
     */
    ChronoTime();

    /**
     * getter for the last  meeting that was set in the program.
     * @return system clock until the next meeting.
     */
    const std::chrono::system_clock::time_point& getMeetingTime() const;

    /**
     * setter for a new metting.
     * @param meetingTime
     */
    void setMeetingTime(const std::chrono::system_clock::time_point& meetingTime);


    std::string stringCurrentTime();

    /**
     * getter for the current time.
     * @return
     */
    std::chrono::system_clock::time_point getCurrentTime();
};

#endif // ROBOT_NAVIGATION_WORKSHOP_CHRONOTIME_H
