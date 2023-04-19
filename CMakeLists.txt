cmake_minimum_required(VERSION 3.24)

project(Robot-Navigation-Workshop)

# Add the cmake directory to the module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find playerc++ library and headers
find_package(playerc++ REQUIRED)
include_directories(${PLAYERCXX_INCLUDE_DIRS})

# Add the executable
add_executable(Robot-Navigation main.cpp
        src/Navigation.cpp
        src/Navigation.h src/Route.cpp src/Route.h)

# Link the playerc++ library
target_link_libraries(robot ${PLAYERCXX_LIBRARIES})
