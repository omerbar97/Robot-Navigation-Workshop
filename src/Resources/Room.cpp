//
// Created by ofirhelerman on 4/19/23.
//

#include "Room.h"



int Room::getRoomId() const { return this->roomId; }

Room::Room(std::string roomInfoLine) {
    // getting line in the foramt:
    // room 1 x1 y1 x2 y2 x3 y3
    // where the first one (1) is the centerPoint,
    // the second one (x1 y1) is the entryPoint and the third one (x2 y2) is the exitPoint

    // breaking the line:
    std::vector<std::string> tokens;
    std::stringstream text(roomInfoLine);
    std::string token;

    while (std::getline(text, token, ',')) {
        tokens.push_back(token);
    }
}

