//
// Created by omer on 5/15/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROOMSHANDLER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROOMSHANDLER_H
#include <vector>
#include <string>
#include "Room.h"


/**
 * handle the rooms in the map, reading the rooms from a map
 */
class RoomsHandler {
    // private member
private:
    std::vector<Room> rooms;
    std::vector<int> roomsId;

    void initRooms(std::string roomConfigPath);

public:
    RoomsHandler(std::string roomConfigPath, std::vector<int> roomsIds);

    // public methods
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROOMSHANDLER_H
