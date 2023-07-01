//
// Created by omer on 5/5/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
#define ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
#include <libplayerc++/playerc++.h>
#include <boost/bind/bind.hpp>
#include <string>
#include <nlohmann/json.hpp>
#include <mutex>
#include <utility>

using namespace boost::placeholders;

class RobotWrapper {
private:

    // robot instance
    PlayerCc::PlayerClient* robot;
    PlayerCc::Position2dProxy* positionProxy;
    PlayerCc::RangerProxy* laserProxy;

    bool enableFastTravel;
    bool isRobotOnline;
    int port;
    std::string ip;
    double robotGroundSpeed;
    double robotTurnSpeed;
    std::string ws;
    std::mutex robotMutex;
    int startingRobotDegree;
    std::vector<std::pair<double, double>> robotCurrentPath;

public:

    /**
     * constructor for the robot wrapper class, get all the argument from the calling function.
     * @param robot - PlayerClient
     * @param positionProxy - Position2dProxy
     * @param laserProxy - RangerProxy
     * @param ws the ws string for the live communication (no required)
     */
    RobotWrapper(PlayerCc::PlayerClient* robot, PlayerCc::Position2dProxy* positionProxy, PlayerCc::RangerProxy* laserProxy, std::string ws = nullptr);

    /**
     * constructor for the robot wrapper class, given only the ip, port, and ws (no required) and creating all the instances alone.
     * @param ip - string
     * @param port - int
     * @param ws - string
     */
    RobotWrapper(std::string ip, int port, std::string ws = nullptr);

    /**
     * deleting all the heap memory.
     */
    ~RobotWrapper();

    /**
     * setting new robot speed
     * @param speed - double
     */
    void setRobotSpeed(double speed);

    /**
     * setting new robot rotation speed, in radian.
     * @param speed - double
     */
    void setRobotTurnSpeed(double speed);

    /**
     * setting the actual robot with speed (using mutex to avoid condition race)
     * @param speed - double
     * @param turnSpeed - double
     */
    void setSpeed(double speed, double turnSpeed);

    /**
     * starting the robot, creating all the instances that needed.
     */
    void initRobot();

    /**
     * setting the optimized path calculation on / off.
     * @param flag - bool
     */
    void setFastTravel(bool flag);

    /**
     * getting the current robot Yaw relative to the robot starting Yaw when first initialized.
     * @return double (in radian)
     */
    double getYaw();


    /**
     * getter for the ground speed of the robot.
     * @return double
     */
    double getGroundSpeed();

    /**
     * getter for the turn speed in radian
     * @return  double
     */
    double getTurnSpeed();

    /**
     * getting from the robot the current position.
     * @return pairs of double
     */
    std::pair<double, double> getCurrentPosition();

    // getRobot Extensions
    /**
     * getter for the position driver.
     * @return Position2dProxy
     */
    PlayerCc::Position2dProxy* getPos();

    /**
     * getter for the laser driver.
     * @return RangerProxy
     */
    PlayerCc::RangerProxy* getLaser();

    /**
     * getter for the robot client it self.
     * @return PlayerClient
     */
    PlayerCc::PlayerClient* getClient();

    /**
     * updating the robot reads using mutex to avoid race condition.
     */
    void update();

    /**
     * if the robot is online (connected to the stage) returning true, otherwise false.
     * @return boolean
     */
    bool isOnline();

    /**
     * setting the robot online boolean.
     * @param flag
     */
    void setOnline(bool flag);

    /**
     * getter for the optimized path variable.
     * @return
     */
    bool isFastTravelEnable();

    /**
     * setter for the robot starting degree.
     * @param degree
     */
    void setStartingDegree(int degree);

};


#endif //ROBOT_NAVIGATION_WORKSHOP_ROBOTWRAPPER_H
