//
// Created by ofirhelerman on 4/19/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROOM_H
#define ROBOT_NAVIGATION_WORKSHOP_ROOM_H

#include <utility>
#include <string>
#include <sstream>
#include <vector>

/**
 * A class representing a room in the map.
 */
class Room {
private:
    /// The entry point to the room.
    std::pair<double, double> entryPoint;
    std::pair<double, double> centerPoint;
    std::pair<double, double> exitPoint;
    /// The room's ID.
    int roomId;
    std::string roomName;

public:
    /**
     * Constructs a new room.
     * @param entryPoint The entry point to the room.
     * @param roomId The room's ID.
     */
    Room(std::pair<double, double> centerPoint, std::pair<double, double> entryPoint, std::pair<double, double> exitPoint,
         int roomId);

    explicit Room(const std::string& roomInfoLine);

    /**
     * Gets the entry point to the room.
     * @return The entry point to the room.
     */
    const std::pair<double, double>& getEntryPoint() const;

        /**
     * Gets the entry point to the room.
     * @return The entry point to the room.
     */
     const std::pair<double, double>& getCenterPoint() const;

        /**
     * Gets the entry point to the room.
     * @return The entry point to the room.
     */
        const std::pair<double, double> & getExitPoint() const;

    /**
     * Gets the room's ID.
     * @return The room's ID.
     */
    const int& getRoomId() const;


    const std::string & getRoomName() const;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROOM_H
