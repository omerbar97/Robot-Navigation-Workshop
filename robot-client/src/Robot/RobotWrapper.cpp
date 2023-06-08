//
// Created by omer on 5/5/23.
//

#include "RobotWrapper.h"

//RobotWrapper::RobotWrapper(std::string robotIp, int robotPort, int groundSpeed, int turnSpeed) {
//    this->initRobot(robotIp, robotPort);
//    this->robotGroundSpeed = groundSpeed;
//    this->robotTurnSpeed = turnSpeed;
//}

RobotWrapper::RobotWrapper(PlayerCc::PlayerClient &robot, PlayerCc::Position2dProxy &positionProxy,
                           PlayerCc::RangerProxy &laserProxy, std::string ws) :
        robot(robot), positionProxy(positionProxy), laserProxy(laserProxy) {
    this->robotTurnSpeed = 0.03;
    this->robotGroundSpeed = 0.06;
    this->isRobotOnline = true;
    // connecting to the server with ip: ws
    this->clientWs = new client();
    this->clientWs->init_asio();
    websocketpp::lib::error_code ec;
    client::connection_ptr con = this->clientWs->get_connection(ws, ec);
    if (ec) {
        std::cout << "Failed to create connection: " << ec.message() << std::endl;
        delete this->clientWs;
        this->clientWs = nullptr;
    } else {
//        std::thread t([this, con]() {
            this->startClient(con);
//        });
//        t.detach();
    }
}


RobotWrapper::~RobotWrapper() {
//    if (this->positionProxy != nullptr) {
//        delete this->positionProxy;
//        this->positionProxy = nullptr;  // Set the pointer to null after deleting.
//    }
//    if (this->laserProxy != nullptr) {
//        delete this->laserProxy;
//        this->laserProxy = nullptr;  // Set the pointer to null after deleting.
//    }
//    this->getClient().Disconnect();
}

void RobotWrapper::setRobotPath(std::pair<double, double> path) {
    this->robotCurrentPath = path;
}

void RobotWrapper::setRobotSpeed(double speed) {
    this->robotGroundSpeed = speed;
}

void RobotWrapper::setRobotTurnSpeed(double speed) {
    this->robotTurnSpeed = speed;
}

PlayerCc::Position2dProxy &RobotWrapper::getPos() {
    return this->positionProxy;
}

PlayerCc::RangerProxy &RobotWrapper::getLaser() {
    return this->laserProxy;
}

PlayerCc::PlayerClient &RobotWrapper::getClient() {
    return this->robot;
}

void RobotWrapper::initRobot(std::string robotIp, int robotPort) {
//    std::cout << "connection to robot: " << robotIp << ":" << robotPort << std::endl;
//    this->positionProxy = new PlayerCc::Position2dProxy(&this->robot, 0);
//    std::cout << "connection to robot position proxy" << std::endl;
//    this->laserProxy = new PlayerCc::LaserProxy(&this->robot, 0);
//    std::cout << "connection to robot laser proxy" << std::endl;
}

double RobotWrapper::getGroundSpeed() {
    return this->robotGroundSpeed;
}

double RobotWrapper::getTurnSpeed() {
    return this->robotTurnSpeed;
}

std::pair<double, double> RobotWrapper::getCurrentPosition() {
    this->update();
    return std::make_pair(this->positionProxy.GetXPos(), this->positionProxy.GetYPos());
}

void RobotWrapper::update() {
    try {
        while (this->robot.Peek()) {
            usleep(50);
            this->robot.Read();
        }
    } catch (PlayerCc::PlayerError &e) {
//        std::cerr << e << std::endl;
    }
}

bool RobotWrapper::isObstacleOnLeft() {
    // using the rangerproxy to check if there is an obstacle on the left
    // if there is an obstacle on the left, return true
    // else return false
    this->update();
    PlayerCc::RangerProxy &ranger = this->getLaser();
    // Get the total number of range readings
    int numReadings = ranger.GetRangeCount();
    // Calculate the number of readings on the left side
    int numReadingsOnLeft = numReadings / 2;
    // Define a threshold value for obstacle detection
    double obstacleThreshold = 0.5; // Adjust this value as needed
    // Check for obstacles on the left side
    for (int i = 0; i < numReadingsOnLeft; i++) {
        double range = ranger[i];
        if (range < obstacleThreshold) {
            // An obstacle is detected on the left side
            return true;
        }
    }
    // No obstacles found on the left side
    return false;
}

bool RobotWrapper::isObstacleOnRight() {
    // using the rangerproxy to check if there is an obstacle on the right
    // if there is an obstacle on the right, return true
    // else return false
    this->update();
    PlayerCc::RangerProxy &ranger = this->getLaser();
    // Get the total number of range readings
    int numReadings = ranger.GetRangeCount();
    // Calculate the number of readings on the left side
    int numReadingsOnLeft = numReadings / 2;
    // Define a threshold value for obstacle detection
    double obstacleThreshold = 0.5; // Adjust this value as needed
    // Check for obstacles on the right side
    for (int i = numReadingsOnLeft; i < numReadings; i++) {
        double range = ranger[i];
        if (range < obstacleThreshold) {
            // An obstacle is detected on the right side
            return true;
        }
    }
    // No obstacles found on the right side
    return false;
}

bool RobotWrapper::hasObstaclesOnSides() {
    // Get the total number of range readings
    this->update();
    PlayerCc::RangerProxy &ranger = this->getLaser();
    int numReadings = ranger.GetRangeCount();
    // Define a threshold value for obstacle detection
    double obstacleThreshold = 0.5; // Adjust this value as needed
    // Check for obstacles on both sides
    for (int i = 0; i < numReadings; i++) {
        double range = ranger[i];
        if (range < obstacleThreshold) {
            // An obstacle is detected on either side
            std::cout << "obstacle detected on side" << std::endl;
            return true;
        }
    }
    // No obstacles found on either side
    return false;
}

void RobotWrapper::sendRobotPosition() {
    // sending the robot position to the server
    // the robot position is sent as a json object
    // the json object has the following format:
    // {
    //      "type": "robotPosition",
    //      "data": {
    //          "x": 0.0,
    //          "y": 0.0
    //      }
    // }
    // the x and y values are the robot position
    while (this->isRobotOnline) {
        // get the robot position
        std::pair<double, double> robotPosition = this->getCurrentPosition();
        // create the json object
        nlohmann::json robotPositionJson;
        robotPositionJson["type"] = "robotPosition";
        robotPositionJson["data"]["x"] = robotPosition.first;
        robotPositionJson["data"]["y"] = robotPosition.second;

        // send the json object to the server
        this->clientWs->send(this->hdlServer, robotPositionJson.dump(), websocketpp::frame::opcode::text);
        usleep(5000000); // 5 sec
    }

    // close the connection
    this->clientWs->close(this->hdlServer, websocketpp::close::status::going_away, "");

}

client *RobotWrapper::getWsClient() {
    return this->clientWs;
}

void RobotWrapper::startClient(client::connection_ptr con) {
    // Set up event handlers
    this->clientWs->set_message_handler([](websocketpp::connection_hdl hdl, client::message_ptr msg) {
        // Handle received message
        std::cout << "Received message: " << msg->get_payload() << std::endl;
    });

    this->clientWs->set_open_handler([this](websocketpp::connection_hdl hdl) {
        // Handle connection open
        std::cout << "Connected to server" << std::endl;
        // Send a message after connection is open
        std::string message = "Hello, server! from ROBOT!";
        this->hdlServer = std::move(hdl);
        this->clientWs->send(this->hdlServer, message, websocketpp::frame::opcode::text);
    });

    this->clientWs->set_close_handler([](websocketpp::connection_hdl hdl) {
        // Handle connection close
        std::cout << "Disconnected from server" << std::endl;
    });

    this->clientWs->connect(con);
    this->clientWs->run();
}
