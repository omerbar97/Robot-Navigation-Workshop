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
    std::pair<float, float> entryPoint;
    std::pair<float, float> centerPoint;
    std::pair<float, float> exitPoint;
    /// The room's ID.
    int roomId;
    std::string roomName;

public:
    /**
     * Constructs a new room.
     * @param entryPoint The entry point to the room.
     * @param roomId The room's ID.
     */
    Room(std::pair<float, float> centerPoint, std::pair<float, float> entryPoint, std::pair<float, float> exitPoint,
         int roomId);

    Room(std::string roomInfoLine);

    /**
     * Gets the entry point to the room.
     * @return The entry point to the room.
     */
    std::pair<float, float> getEntryPoint() const;

        /**
     * Gets the entry point to the room.
     * @return The entry point to the room.
     */
    std::pair<float, float> getCenterPoint() const;

        /**
     * Gets the entry point to the room.
     * @return The entry point to the room.
     */
    std::pair<float, float> getExitPoint() const;

    /**
     * Gets the room's ID.
     * @return The room's ID.
     */
    int getRoomId() const;


    std::string getRoomName() const;
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROOM_H
