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

    /**
     * reading the room config file and creating each room.
     * @param roomConfigPath
     */
    void initRooms(const std::string& roomConfigPath);

public:

    /**
     * constructor for the room container class that mange all the rooms.
     * @param roomConfigPath - path to the room config.
     */
    explicit RoomsContainer(const std::string& roomConfigPath);

    /**
     * destructor for all the rooms.
     */
    ~RoomsContainer();

    /**
     * return the room that is associate with the room-id or null if didn't find.
     * @param roomId - int
     * @return
     */
    Room* getRoomById(int roomId);

    /**
     * adding a new room to the database.
     * @param room - Room*
     */
    void addRoom(Room* room);
};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROOMSCONTAINER_H
