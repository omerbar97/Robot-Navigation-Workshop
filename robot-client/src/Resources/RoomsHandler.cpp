//
// Created by omer on 5/15/23.
//

#include "RoomsHandler.h"

/**
 * constructor.
 * @param roomConfigPath - the path to the room config file.
 * @param roomsIds - the ids of the rooms that we want to use.
 */
RoomsHandler::RoomsHandler(std::string roomConfigPath, std::vector<int> roomsIds) {
    this->roomsId = roomsIds;
    this->initRooms(roomConfigPath);
}

void RoomsHandler::initRooms(std::string roomConfigPath) {

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
        Room room(line);
        if(std::find(this->roomsId.begin(), this->roomsId.end(), room.getRoomId()) != this->roomsId.end()) {
            // the room is in the roomsIds vector
            this->rooms.push_back(room);
        }
    }

    // sorting the rooms by id with the same order of roomsIds
    std::vector<Room> newRooms;
    for(int i = 0; i < this->roomsId.size(); i++) {
        int id = this->roomsId[i];
        // searching for the room with the id
        for(int j = 0; j < this->rooms.size(); j++) {
            if (this->rooms[j].getRoomId() == id) {
                newRooms.push_back(this->rooms[j]);
                // removing the room from the rooms vector
                this->rooms.erase(this->rooms.begin() + j);
                break;
            }
        }
    }
    this->rooms = newRooms;
}

std::vector<Room> RoomsHandler::getRooms() const {
    return this->rooms;
}

std::vector<int> RoomsHandler::getRoomsId() const {
    return this->roomsId;
}
