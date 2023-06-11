//
// Created by omer on 5/15/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROOMSCONTAINER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROOMSCONTAINER_H
#include "Room.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>


/**
 * handle the rooms in the map, reading the rooms from a map
 */
using namespace std;
class RoomsContainer {
    // private member
private:
    map<int, Room*> rooms;

    void initRooms(const std::string& roomConfigPath);

public:
    explicit RoomsContainer(const std::string& roomConfigPath);
    ~RoomsContainer();

    Room* getRoomById(int roomId);
    void addRoom(Room* room);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROOMSCONTAINER_H
