cmake_minimum_required(VERSION 3.24)

project(Robot-Navigation-Workshop)

# Add the cmake directory to the module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(OpenCV_DIR /usr/include/opencv2)

# Find playerc++ library and headers
find_package(playerc++ REQUIRED)
include_directories(${PLAYERCXX_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


# Add the executable
add_executable(Robot-Navigation main.cpp src/Route.cpp
        src/Navigation.cpp
        src/Navigation.h
        src/Room.cpp
        src/Room.h
        src/Route.cpp
        src/Route.h src/DataStructure.h)



target_link_libraries(Robot-Navigation ${PLAYERCXX_LIBRARIES})
target_link_libraries(Robot-Navigation ${OpenCV_LIBS})
