# Robot-Navigation-Workshop

## Team-Member
- **Omer Bar**
- **Shilo Padael**
- **Ofir Helerman**

## About

Welcome to our second-year Computer Science project on robot navigation! This repository contains the code and documentation for our exploration into the fascinating field of robot navigation. Our team, consisting of three dedicated and enthusiastic students, aims to develop a robust and efficient navigation system for a mobile robot using the Player/Stage platform and implementing it in C++.

#### Furthermore
Our second-year Computer Science project focuses on developing a robot navigation system using the Player/Stage platform and integrating the Open Motion Planning Library (OMPL) algorithms. We aim to create an autonomous navigation system that enables a mobile robot to navigate its environment efficiently and safely. The project involves perception, mapping, path planning, and control components. By leveraging Player/Stage and OMPL, we will build a robust and optimized system. Throughout the project, we anticipate challenges in algorithm tuning and system integration. The code and documentation in this repository provide an overview of our implementation progress. Join us on this exciting journey into the world of robot navigation!

## Features
- Player/Stage Interface: The program interfaces with the player/stage platform to control the robot's navigation in a specified map.
- C++ Implementation: The codebase is written in C++, ensuring efficiency and performance in robot navigation tasks. Including a server that run the process child of the controller.
- Multithreading: the robot-controller is connecting to the robot and to the Express WebSocket in a seperate thread to send the robot live data.
- Websockets: The application utilizes websockets to establish real-time bidirectional communication between the server and the user interface, ensuring seamless control and live data updates.
- HTTP and Express Server: An HTTP server, built with Express, is included to handle incoming requests and provide a RESTful API for controlling the robot and accessing relevant data.
- React Interface: The user interface is developed using React, offering an intuitive and interactive experience for controlling the robot's movements and accessing various features.
- Live Data Display: The interface provides a live display of real-time data from the robot, such as sensor readings, position updates, and other relevant information.


## Installation

You must have all the program depandances to be able to run it.

Set up the server-interface for localhost use.

```sh
git clone https://github.com/omerbar97/Robot-Navigation-Workshop.git
cd Robot-Navigation-Workshop                // going to project directory
npm run build                               // building the node_mudule and static html file for the server
npm run start-local                         // for localhost
```

Set up the C++ Server, inside the Robot-Navigation-Workshop folder do:
```sh
cd robot-client                             // going to project directory
mkdir build                                 // creating a new folder
cd build                                    
cmake ../                                   // creating the makefile
make                                        // compiling the program
./Server 'ip' 'port'                        // example ./Server localhost 9000
```
**Do the example to avoid changes to do in the backend server.**

### Alternative (simple version)
If you wish to run this program without the unnecessary depandances of the server side you will need to install only those things:
<ul>
  <li>Player + Stage</li>
  <li>cmake</li>
  <li>OMPL (for path planning)</li>
  <li>Espeak (for text to speach)</li>
  <li>OpenCv (for img handle)</li>
</ul>

Afterward you should be able to run the CLI version only in the robot-client-simple folder.

Inside the project folder go to robot-client-simple and do:
```
mkdir build                                 // creating a new folder
cd build                                    
cmake ../                                   // creating the makefile
make                                        // compiling the program
./Robot-Navigation                          // starting the robot CLI
```

## Dependances
##### You Must Have Linux Machine
Make sure to install all the dependances to be able to run our program
| Dependances | Link |
| ------ | ------ |
| Git | [https://git-scm.com/downloads]|
| Player + Stage| [https://playerstage.sourceforge.net/]|
| OMPL | [https://github.com/ompl/ompl]|
| Espeak | [https://espeak.sourceforge.net/]|
| Json for C++ | [https://github.com/nlohmann/json]|
| cmake | [https://cmake.org/download/]|
| websocketcpp | [[https://cmake.org/download/](https://github.com/zaphoyd/websocketpp/)]|
| curl | [https://curl.se/libcurl/c/]|
| opencv | [https://github.com/opencv/opencv/tree/4.7.0]|
