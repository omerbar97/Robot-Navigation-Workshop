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

}