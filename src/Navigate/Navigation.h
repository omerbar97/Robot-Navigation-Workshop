//
// Created by omer on 4/19/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
#define ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
#include <vector>
#include <string>
#include "../PathPlanning/Route.h"
#include "../Resources/Room.h"
#include "Navigatable.h"
#include "../Behavior/Mission.h"

class Navigation : public Mission {
private:

    // new members
    Navigatable* navigatable;
    Route* route;
    std::pair<double, double> currentPosition;
    std::pair<double, double> destination;
    Behavior* behavior;

    /**
     * set the behavior that will be executed when the navigatable object is navigating.
     * this is private going to call it from the setMission method.
     * @param behavior
     */
    void setBehavior(Behavior* behavior);


public:

    /**
     * constructor.
     * @param navigatable - the navigatable object that will be navigated.
     */
    Navigation(Navigatable* navigatable);

    /**
     * constructor. (with behavior) the behavior is the logic that the navigatable object will execute
     * will navigate the object to the given destination.
     * @param navigatable
     * @param behavior
     * @param currentPosition
     * @param destination
     */
    Navigation(Navigatable* navigatable, Behavior* behavior, Algorithm* algorithm,std::pair<double, double> currentPosition,
               std::pair<double, double> destination);

    /**
     * destructor.
     */
    ~Navigation();

    // setters
    /**
     * set the algorithm that will be used to calculate the path. in the route class
     * @param algorithm
     */
    void setRouteAlgorithm(Algorithm* algorithm);

    /**
     * set the map generator that will be used to create the gridMap. in the route class.
     * @param mapGenerator
     */
    void setMapGenerator(MapGenerator* mapGenerator);



    /**
     * set the current position of the navigatable object.
     * @param currentPosition
     */
    void setCurrentPosition(std::pair<double, double> currentPosition);

    /**
     * set the destination of the navigatable object.
     * @param destination
     */
    void setDestination(std::pair<double, double> destination);


    /**
     * start the navigation. the navigation will start the behavior and the navigatable object will start to navigate.
     */
    void start();

    // override method
    /**
     * set the mission of the navigatable object.
     * @param mission
     */
    void setMission(Behavior *behavior);

    /**
     * do the mission of the navigatable object.
     * @return
     */
     void doMission();

};


#endif //ROBOT_NAVIGATION_WORKSHOP_NAVIGATION_H
