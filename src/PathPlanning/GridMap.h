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

    // private members
    const ompl::base::RealVectorBounds bounds;
    int width;
    int height;
    int scale; // in case each pixel going to be more than one pixel in the map

    /**
     * creating the gridMap by different scale if needed.
     * @param gridMatrix
     * @param scale
     */
    void initGridMap(const cv::Mat* gridMatrix, int scale=1);

public:

    /**
     * constructor for the gridmap, the gridMap class is kind of a RealVectorStateSpace, so we need to give it
     * a matrix with 0,1 values and the dim of the matrix.
     * @param pixelMap
     * @param dim
     */
    GridMap(cv::Mat* pixelMap, std::size_t dim, int scale=1);
    ~GridMap();

    // getters
    int getWidth() const;
    int getHeight() const;
    int getScale() const;

    // setters
    void setWidth(int width);
    void setHeight(int height);
    void setScale(int scale);

    //override
    bool isValid(const ompl::base::State *state) const;


};


#endif //ROBOT_NAVIGATION_WORKSHOP_GRIDMAP_H
