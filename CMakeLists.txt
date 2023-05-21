cmake_minimum_required(VERSION 3.24)
project(Robot-Navigation-Workshop)

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

# Add the executables
add_executable(Robot-Navigation
        main.cpp
        src/Navigate/Navigation.cpp
        src/Navigate/Navigation.h
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
        src/Resources/RoomsHandler.h
        src/Resources/RoomsHandler.cpp
        src/Robot/RobotWrapper.h
        src/Robot/RobotWrapper.cpp
        src/Behavior/RobotBehavior/RobotBehavior.h
        src/Behavior/RobotBehavior/RobotBehavior.cpp
        src/Behavior/RobotBehavior/HallNavigateBehavior.cpp
        src/Behavior/RobotBehavior/HallNavigateBehavior.h
        src/Behavior/RobotBehavior/RotationBehavior.h
        src/Behavior/RobotBehavior/RotationBehavior.cpp
        src/Behavior/Behavior.h)

# Link the playerc++, OpenCV, and OMPL libraries
find_package(OpenCV CONFIG REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_include_directories(Robot-Navigation PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(Robot-Navigation ${PLAYERCXX_LIBRARIES} ${OpenCV_LIBS} ${OMPL_LIBRARY})
