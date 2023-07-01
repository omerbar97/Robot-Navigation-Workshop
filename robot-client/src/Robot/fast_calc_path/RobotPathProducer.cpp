//
// Created by shilopadael on 6/30/23.
//


#include "RobotPathProducer.h"



RobotPathProducer::RobotPathProducer(MissionDataList *data, RoomsContainer* roomsContainer, MapGenerator *map) {
    this->data = data;
    this->roomsContainer = roomsContainer;
    this->map = map;
    unsigned int numMissions = data->size();
    this->path = new MissionPathList(numMissions);
}

MissionPathList* RobotPathProducer::createPaths() {
    std::vector<std::thread> threads;
    for (int i = 0; i < data->size(); i++) {
        Point startPoint = roomsContainer->getRoomById(data->at(i).first)->getEntryPoint();
        int startRoomID = data->at(i).first;
        Point goalPoint = roomsContainer->getRoomById(data->at(i).second)->getEntryPoint();
        int goalRoomID = data->at(i).second;
        std::thread creator(PathCreator(startPoint, startRoomID, goalPoint, goalRoomID, this->map,
                                        this->path, i));
        threads.push_back(std::move(creator));
    }

    for (auto & thread : threads) {
        thread.join();
    }
    return this->path;
}




