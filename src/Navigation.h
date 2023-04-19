//
// Created by omer on 4/19/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
#define ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
#include <vector>
#include <string>
#include "Route.h"
#include "libplayerc++/playerc++.h"

class Navigation {
private:
    // variables
    std::vector<Room> rooms;
    Route* route;
    std::vector<short> roomsIdToGo;
    PlayerCc::PlayerClient* robot;


    //private methods
    /**
     * initlizing the rooms vector from the given file path.
     * @param filePath
     */
    void initRooms(std::string filePath);

    /**
     * navigate to the given room id.
     * @param roomId short
     */
    void navigate(short roomId);

    /**
     * set the current room to the given id.
     * @param id short
     */
    void setRoomToCurrentNavigation(short id);

public:

    /**
     * constructor.
     * @param pathToRooms
     * @param robot
     */
    Navigation(std::string pathToRooms, PlayerCc::PlayerClient* robot);

    /**
     * destructor.
     */
    ~Navigation();

    // public methods
    /**
     * set the rooms to go to the given vector of rooms id.
     * @param roomsId  std::vector<short>
     */
    void setRoomsToRoute(std::vector<short> roomsId);

    /**
     * start the navigation.
     */
    void start();
};


#endif //ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
