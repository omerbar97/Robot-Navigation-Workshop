cmake_minimum_required(VERSION 3.24)
project(Robot-Navigation-Workshop)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-dev")

# Add the cmake directory to the module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")



# Find playerc++ library and headers
find_package(playerc++ REQUIRED)
include_directories(${PLAYERCXX_INCLUDE_DIRS})

# Find OpenCV library
set(OpenCV_DIR /usr/local/lib)

# Find OMPL library
find_library(OMPL_LIBRARY
        NAMES libompl.so.1.6.0 libompl.so.17 libompl.so
        PATHS /usr/local/lib
        REQUIRED
        )
include_directories(${OMPL_INCLUDE_DIRS})

find_package(jsoncpp CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

# Add the executables
add_executable(Robot-Navigation
        main.cpp
        src/PathPlanning/Route.cpp
        src/PathPlanning/Route.h
        src/Resources/MapGenerator.cpp
        src/Resources/MapGenerator.h
        src/PathPlanning/GridMap.h
        src/PathPlanning/GridMap.cpp
        src/PathPlanning/GridMapValidityChecker.cpp
        src/PathPlanning/GridMapValidityChecker.h
        src/PathPlanning/Algorithm/Algorithm.h
        src/PathPlanning/Algorithm/Algorithm.cpp
        src/PathPlanning/Algorithm/RRTStarAlgorithm.cpp
        src/PathPlanning/Algorithm/RRTStarAlgorithm.h
        src/Resources/Room.cpp
        src/Resources/Room.h
        src/Resources/RoomsContainer.h
        src/Resources/RoomsContainer.cpp
        src/Robot/RobotWrapper.h
        src/Robot/RobotWrapper.cpp
        src/Behavior/RobotBehavior/RobotBehavior.h
        src/Behavior/RobotBehavior/RobotBehavior.cpp
        src/Behavior/RobotBehavior/HallNavigateBehavior.cpp
        src/Behavior/RobotBehavior/HallNavigateBehavior.h
        src/Behavior/RobotBehavior/RotationBehavior.h
        src/Behavior/RobotBehavior/RotationBehavior.cpp
        src/Behavior/Behavior.h
        src/Behavior/MessageBehavior/MessageBehavior.h
        src/Behavior/MessageBehavior/VoiceMessageBehavior.cpp
        src/Behavior/MessageBehavior/VoiceMessageBehavior.h
        src/Client/WebSocketClient.h
        src/Client/WebSocketClient.cpp
        src/Behavior/RobotBehavior/EnterRoomBehavior.cpp
        src/Behavior/behaviour-functors/LinearNavigation.cpp
        src/Behavior/behaviour-functors/LinearNavigation.h
        src/Behavior/RobotBehavior/ExitRoomBehavior.h
        src/Behavior/RobotBehavior/ExitRoomBehavior.cpp
        src/Robot/RobotPlanner.h src/Robot/RobotPlanner.cpp
        src/Robot/RobotCLI.cpp
        src/Robot/RobotCLI.h
        src/Missions/navigation-missions/R2R.cpp
        src/Behavior/behaviour-functors/RotateRobot.cpp
        src/Behavior/behaviour-functors/RotateRobot.h
        src/Missions/factories/nav-mission-factory/NavigationMissionsFactory.cpp
        src/Missions/factories/nav-mission-factory/NavigationMissionsFactory.h
        src/Missions/factories/nav-mission-factory/NavigationMissionsFactory.h src/Missions/factories/MissionFactory.h src/Behavior/behaviour-functors/AvoidObstacle.h src/Behavior/behaviour-functors/AvoidObstacle.cpp src/Robot/Colors.h src/Missions/CalculateTime.h src/Missions/CalculateTime.cpp src/Missions/navigation-missions/R2Exit.h src/Missions/navigation-missions/R2Exit.cpp src/Missions/Inform-Missions/Inform.h src/Missions/Inform-Missions/Inform.cpp)

add_executable(Server
        server/main.cpp
        server/WebSocketServer.cpp
        server/WebSocketServer.h
        server/Helper.cpp
        server/Helper.h)


# Link the playerc++, OpenCV, and OMPL libraries
find_package(OpenCV CONFIG REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_include_directories(Robot-Navigation PRIVATE ${OpenCV_INCLUDE_DIRS} ${jsoncpp} ${jsoncpp_INCLUDE_DIRS})
target_link_libraries(Robot-Navigation ${PLAYERCXX_LIBRARIES} ${OpenCV_LIBS} ${OMPL_LIBRARY} OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(Server PRIVATE curl ssl crypto)

