//
// Created by omer on 5/8/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_GRIDMAP_H
#define ROBOT_NAVIGATION_WORKSHOP_GRIDMAP_H
#include <ompl/base/StateSpace.h>
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <opencv2/opencv.hpp>

class GridMap : public ompl::base::RealVectorStateSpace {
    /**
     * this class is the representation of the grid map, the class MapGenerator create a map using the opencv
     * library and the matrix map of (0,1) should be given to this class appon creation.
     */

private:

    cv::Mat* gridMatrix;
    ompl::base::RealVectorBounds* bounds;

    /**
     * girdMap members
     */
    int width;
    int height;

    /**
     * for now, each pixel is just a normal pixel in the future we will implement the scale. such that each pixel in the matrix
     * will correspond to the kind of measure in the real world, for example each pixel will be 20x20 cm so the matrix will
     * be much smaller.
     */
    int scale;


public:

    /**
     * constructor for the gridmap, the gridMap class is kind of a RealVectorStateSpace, so we need to give it
     * a matrix with 0,1 values and the dim of the matrix.
     * @param pixelMap
     * @param dim
     */
    GridMap(cv::Mat* pixelMap, int scale);

    /**
     * copy constructor
     * @param gridMap
     */
    GridMap(const GridMap& gridMap);

    /**
     * destructor for the gridMap, deleting all the members.
     */
    ~GridMap();

    // getters
    int getWidth() const;
    int getHeight() const;
    ompl::base::RealVectorBounds *getBounds();
    cv::Mat* getGridMatrix() const;


    /**
     * setter for a new gridMatrix, the gridMatrix is the matrix of the grid map. need to delete the old ones and basically
     * create a new one.
     * @param gridMatrix
     */
    void setGridMatrix(cv::Mat* gridMatrix);



};


#endif //ROBOT_NAVIGATION_WORKSHOP_GRIDMAP_H
