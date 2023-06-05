//
// Created by ofirhelerman on 4/19/23.
//

#include "Room.h"



int Room::getRoomId() const { return this->roomId; }

Room::Room(std::string roomInfoLine) {
    // getting line in the foramt:
    // roomname 1 x1 y1 x2 y2 x3 y3
    // where the first one (1) is the centerPoint,
    // the second one (x1 y1) is the entryPoint and the third one (x2 y2) is the exitPoint

    // breaking the line:
    std::vector<std::string> tokens;
    std::stringstream text(roomInfoLine);
    std::string token;

    while (std::getline(text, token, ' ')) {
        tokens.push_back(token);
    }

    // getting the room name:
    this->roomName = tokens[0];

    // getting room id
    this->roomId = std::stoi(tokens[1]);

    // getting center point
    this->centerPoint = std::make_pair(std::stof(tokens[2]), std::stof(tokens[3]));

    //getting entry point
    this->entryPoint = std::make_pair(std::stof(tokens[4]), std::stof(tokens[5]));

    // getting exit point
    this->exitPoint = std::make_pair(std::stof(tokens[6]), std::stof(tokens[7]));
}

std::pair<float, float> Room::getEntryPoint() const {
    return this->entryPoint;
}

std::pair<float, float> Room::getCenterPoint() const {
    return this->centerPoint;
}

std::pair<float, float> Room::getExitPoint() const {
    return this->exitPoint;
}

std::string Room::getRoomName() const {
    return this->roomName;
}