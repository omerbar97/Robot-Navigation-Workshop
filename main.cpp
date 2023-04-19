#include <iostream>
#include <libplayerc++/playerc++.h>

int main(int argc, char **argv) {
    // Set up the PlayerClient object
    PlayerCc::PlayerClient client("localhost", 6665);
    PlayerCc::Position2dProxy position(&client, 0);

    // Attempt to connect to the server
    std::cout << "Connecting to Player/Stage server..." << std::endl;
    std::string hostname = "localhost";
    int port = 6665;
    std::cout << "Successfully connected to Player/Stage server." << std::endl;

    // Wait for data to be available
    while(true) {
        client.Read();
        position.SetSpeed(0.8, 0);
        // Wait for a few seconds
        sleep(1);

        // Print the robot's position
        std::cout << "Robot position: (" << position.GetXPos() << ", " << position.GetYPos() << ")" << std::endl;
    }

    return 0;
}
