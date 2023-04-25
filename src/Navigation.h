//
// Created by omer on 4/19/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
#define ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
#include <vector>
#include <string>
#include "Route.h"
#include "libplayerc++/playerc++.h"
#include "Room.h"

class Navigation {
private:
    // variables
    int mapWidth;
    int mapHeight;
    int blockPixels;
    int numOfBlocksWidth;
    int numOfBlocksHeight;
    std::vector<Room> rooms;
    Route* route;
    std::vector<short> roomsIdToGo;
    PlayerCc::PlayerClient* robot;
    PlayerCc::Position2dProxy* robotPosition;

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

    /**
     * convert the given stage coordinates to pixel coordinates.
     * @param x double
     * @param y double
     * @param pixel_x int
     * @param pixel_y int
     * @param scale double
     */
    void stageToPixel(double x, double y, int& pixel_x, int& pixel_y, double scale);

    /**
     * convert the given pixel coordinates to stage coordinates.
     * @param pixel_x int
     * @param pixel_y int
     * @param x double
     * @param y double
     * @param scale double
     */
    void pixelToStage(int pixel_x, int pixel_y, double& x, double& y, double scale);

    /**
     * travel to the given points. each point is a pair of doubles. the first is the x coordinate and the second is the y coordinate.
     * @param points std::vector<std::pair<double, double>>
     */
    void travelToPoints(std::vector<std::pair<double, double>> points);

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
