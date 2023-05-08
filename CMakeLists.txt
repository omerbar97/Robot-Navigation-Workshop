cmake_minimum_required(VERSION 3.24)

project(Robot-Navigation-Workshop)

# Add the cmake directory to the module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# Find playerc++ library and headers
find_package(playerc++ REQUIRED)
include_directories(${PLAYERCXX_INCLUDE_DIRS})


# Find OpenCV library
# Find OpenCV library
set(OpenCV_DIR /usr/local/lib)

# Add the executables
add_executable(Robot-Navigation main.cpp
        src/Navigate/Navigation.cpp
        src/Navigate/Navigation.h
        src/Resources/Room.cpp
        src/Resources/Room.h
        src/PathPlanning/Route.cpp
        src/PathPlanning/Route.h
        src/Resources/MapGenerator.cpp
        src/Resources/MapGenerator.h src/PathPlanning/GridMap.h)


# Link the playerc++ and OpenCV libraries
find_package(OpenCV CONFIG REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_include_directories(Robot-Navigation PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(Robot-Navigation ${PLAYERCXX_LIBRARIES} ${OpenCV_LIBS})



