//
// Created by shilopadael on 6/30/23.
//

#include <iomanip>
#include "ChronoTime.h"



ChronoTime::ChronoTime() {

}

std::chrono::system_clock::time_point ChronoTime::getCurrentTime() {
    return std::chrono::system_clock::now();
}

const std::chrono::system_clock::time_point& ChronoTime::getMeetingTime() const {
    return meetingTime;
}

void ChronoTime::setMeetingTime(const std::chrono::system_clock::time_point& meetingTime) {
    ChronoTime::meetingTime = meetingTime;
}

std::string ChronoTime::convertTimeToString(const std::chrono::system_clock::time_point &timePoint) {

        // Convert the system_clock time_point to a time_t object
        std::time_t currentTime = std::chrono::system_clock::to_time_t(timePoint);

        // Convert the time_t object to a struct tm
        std::tm* timeInfo = std::localtime(&currentTime);

        // Create a stringstream to format the time
        std::stringstream ss;
        ss << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");

        // Return the formatted time as a string
        return ss.str();


}

std::string ChronoTime::stringCurrentTime() {
    return convertTimeToString(getMeetingTime());
}

