//
// Created by omer on 5/15/23.
//

#include "RoomsContainer.h"

/**
 * constructor.
 * @param roomConfigPath - the path to the room config file.
 * @param roomsIds - the ids of the rooms that we want to use.
 */
RoomsContainer::RoomsContainer(const std::string& roomConfigPath) {
    this->initRooms(roomConfigPath);
}

/**
 * destructor.
 */
RoomsContainer::~RoomsContainer() {
    for (auto& room : this->rooms) {
        delete room.second;
    }
}

void RoomsContainer::initRooms(const std::string &roomConfigPath) {

        // iterating through the rooms line and creating a room object for each one
        std::ifstream roomsConfigFile(roomConfigPath);

        // checking if the file is open
        if (!roomsConfigFile.is_open()) {
            std::cout << "Error opening file" << std::endl;
            return;
        }

        // reading the file line by line
        std::string line;
        while(std::getline(roomsConfigFile, line)) {
            // creating new room
            Room* room = new Room(line);
            this->rooms[room->getRoomId()] = room;
        }
}


Room *RoomsContainer::getRoomById(int roomId) {
    return this->rooms[roomId];
}

void RoomsContainer::addRoom(Room *room) {
    this->rooms[room->getRoomId()] = room;
}


