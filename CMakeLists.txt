cmake_minimum_required(VERSION 3.24)

project(Robot-Navigation-Workshop)

# Add the cmake directory to the module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find playerc++ library and headers
find_package(playerc++ REQUIRED)
include_directories(${PLAYERCXX_INCLUDE_DIRS})

# Find OpenCV library
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add the executables
add_executable(Robot-Navigation main.cpp
        src/Navigation.cpp
        src/Navigation.h
        src/Room.cpp
        src/Room.h
        src/Route.cpp
        src/Route.h)

add_executable(robot main.cpp MapGenrator.cpp MapGenrator.h)

# Link the playerc++ and OpenCV libraries
target_link_libraries(Robot-Navigation ${PLAYERCXX_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries(robot ${OpenCV_LIBS})
