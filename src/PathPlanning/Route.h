//
// Created by omer on 4/19/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROUTE_H
#define ROBOT_NAVIGATION_WORKSHOP_ROUTE_H
#include <vector>
#include "../Resources/MapGenerator.h"
#include "Algorithm/Algorithm.h"
#include "GridMap.h"

/**
 * this class is the main class of the path planning, can change the algorithm and the map generator
 * when creating this class it will create alone the gridMap from the mapGenerator.
 * the class will calculate the path and save it in the path vector.
 */
class Route {
private:

    /**
     * the route class has the gridMap inside it, the gridMap is created in this class.
     */
    GridMap* gridMap;
    MapGenerator* mapGenerator;
    Algorithm* algorithm;
    int matrixWidth;
    int matrixHeight;

    /**
     * this method insert the gridMap pointer to the algorithm, and delete the old gridMap.
     */
    void initGridMapToAlgorithm();

    /**
     * this method take a point in the stage coordinates and convert it to the matrix coordinates.
     * @param point - the point in the stage coordinates.
     * @return - the point in the matrix coordinates.
     */
    std::pair<int, int> stageToMatrix(std::pair<double, double> point) const;

    /**
     * this method take a point in the matrix coordinates and convert it to the stage coordinates.
     * @param point - the point in the matrix coordinates.
     * @return - the point in the stage coordinates.
     */
    std::pair<double, double> matrixToStage(std::pair<int, int> point) const;

public:

    /**
     * the MapGenerator will be used to create the gridMap, and the algorithm will be used to calculate the path.
     * @param algorithm - the algorithm to calculate the path.
     * @param mapGenerator - the map generator to create the gridMap.
     */
    Route(Algorithm* algorithm, MapGenerator* mapGenerator);

    /**
     * the MapGenerator will be used to create the gridMap, if an algorithm is not given the default algorithm will be
     * used to calculate the path. needs to decide which algorithm to use.
     * @param mapGenerator - the map generator to create the gridMap.
     */
    Route(MapGenerator* mapGenerator);

    /**
     * destructor for the Route class. need to delete all the objects that are created in the class.
     */
    ~Route();


    // setters upon update need to reload the gridMap to the algorithm and to delete unused objects
    void setGridMap(GridMap* gridMap);
    void setMapGenerator(MapGenerator* mapGenerator);
    void setAlgorithm(Algorithm* algorithm);

    // algorithm setter, setting the point as it is in the stageMap, then transforming it to the matrix coordinates
    void setStartingPoint(std::pair<double ,double> start);
    void setGoalPoint(std::pair<double ,double> goal);

    // do the calculation
    void createPath();

    // get the path, doing the conversion from the gridMap to the real world coordinates, the answer of the algorithm
    // is in the algorithm attributes called pathInMatrix, converting it to the real world coordinates and saving it
    std::vector<std::pair<double ,double>> getStagePath() const;



};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROUTE_H
