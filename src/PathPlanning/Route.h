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
    GridMap* gridMap;
    MapGenerator* mapGenerator;
    Algorithm* algorithm;
    int matrixWidth;
    int matrixHeight;

    void initGridMapToAlgorithm();
    std::pair<int, int> stageToMatrix(std::pair<double, double> point) const;
    std::pair<double, double> matrixToStage(std::pair<int, int> point) const;

public:

    Route(Algorithm* algorithm, MapGenerator* mapGenerator);
    Route(MapGenerator* mapGenerator);
    ~Route();


    // setters uppon update need to reload the gridMap to the algorithm and to delete unused objects
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
