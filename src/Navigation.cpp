//
// Created by omer on 4/19/23.
//

#include "Navigation.h"

void Navigation::navigate(short roomId) {
    // getting room id
    Room room = this->rooms[roomId];
    std::pair<float, float> endPoint = room.getEntryPoint();
    std::pair<double, double> startPoint;
    startPoint.first = this->robotPosition->GetXPos();
    startPoint.second = this->robotPosition->GetYPos();

    // generating path to end point
    std::vector<std::pair<float, float>> currentRoute = this->route->createRoute(startPoint, endPoint);

    // navigation to end point
    for (std::pair<float, float> point : currentRoute) {
        this->robotPosition->SetSpeed(point.first, point.second);
    }
}

void Navigation::stageToPixel(double x, double y, int &pixel_x, int &pixel_y, double scale) {
    // The dimensions of the stage map
    const int blockWidthHeight = this->mapWidth / this->numOfBlocksWidth;
    const int blockWidthHeightPixel = this->mapHeight / this->numOfBlocksHeight;

    // Convert the x-coordinate to pixel coordinate
    pixel_x = static_cast<int>((x + this->numOfBlocksWidth / 2) * blockWidthHeight);

    // Convert the y-coordinate to pixel coordinate
    pixel_y = static_cast<int>((this->numOfBlocksHeight / 2 - y) * blockWidthHeightPixel);
}

void Navigation::pixelToStage(int pixel_x, int pixel_y, double &x, double &y, double scale) {
    // The dimensions of the stage map
    const int blockWidthHeight = this->mapWidth / this->numOfBlocksWidth;
    const int blockWidthHeightPixel = this->mapHeight / this->numOfBlocksHeight;

    // Convert the pixel x-coordinate to stage coordinate
    x = (static_cast<double>(this->numOfBlocksWidth / 2) * blockWidthHeight - static_cast<double>(pixel_x)) / (-blockWidthHeight);
    // Convert the pixel y-coordinate to stage coordinate
    y = (static_cast<double>(this->numOfBlocksHeight / 2)* blockWidthHeightPixel - static_cast<double>(pixel_y)) / blockWidthHeightPixel;
}

void Navigation::travelToPoints(std::vector<std::pair<double, double>> points) {
    // Set the robot's speed and angular velocity
    double speed = 0.09f;
    double fast_angular_velocity = 0.08f;
    double angular_velocity = 0.02f;

    // Loop through each point and travel to it
    for (auto point : points)
    {
        double x = point.first;
        double y = point.second;
        std::cout << "Moving to point: " << x << ", " << y << std::endl;

        // Calculate the angle to the point
        robot.Read();
        double angle = atan2(y - this->robotPosition->GetYPos(), x - this->robotPosition->GetXPos());

        // Turn the robot towards the point
        this->robotPosition->SetSpeed(0, angular_velocity);
        double error = std::remainder(angle - this->robotPosition->GetYaw(), 2 * M_PI);
        while (std::abs(error) > 0.1) {
            this->robotPosition->SetSpeed(0, fast_angular_velocity * std::copysign(1.0, error));
            this->robot->Read();
            error = std::remainder(angle - this->robotPosition->GetYaw(), 2 * M_PI);
            usleep(100);
        }
        robot->Read();
        error = std::remainder(angle -this->robotPosition->GetYaw(), 2 * M_PI);
        while (std::abs(error) > 0.01) {
            this->robotPosition->SetSpeed(0, angular_velocity * std::copysign(1.0, error));
            robot->Read();
            error = std::remainder(angle - this->robotPosition->GetYaw(), 2 * M_PI);
            usleep(10);
        }
        this->robotPosition->SetSpeed(0, 0);

        // Move the robot towards the point
        double distance = std::sqrt(std::pow(y - this->robotPosition->GetYPos(), 2) + std::pow(x - this->robotPosition->GetXPos(), 2));
        while (distance > 0.4) {
            this->robotPosition->SetSpeed(speed, 0);
            robot->Read();
            distance = std::sqrt(std::pow(y - this->robotPosition->GetYPos(), 2) + std::pow(x - this->robotPosition->GetXPos(), 2));
            usleep(100);
        }
        this->robotPosition->SetSpeed(0, 0);
        std::cout << "Reached point: " << x << ", " << y << std::endl;
    }
}

