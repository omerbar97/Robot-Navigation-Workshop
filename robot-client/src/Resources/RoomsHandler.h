//
// Created by omer on 5/15/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROOMSHANDLER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROOMSHANDLER_H
#include "Room.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


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

    std::vector<Room> getRooms() const;

    std::vector<int> getRoomsId() const;
    // public methods
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROOMSHANDLER_H
