# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.24)

# Define a CMake module to find OpenCV
# Usage: find_package(OpenCV REQUIRED)
# Outputs: OpenCV_FOUND, OpenCV_INCLUDE_DIRS, OpenCV_LIBRARIES
if(WIN32)
    set(OpenCV_DIR "C:/path/to/OpenCV")
endif()


if(OpenCV_FOUND)
    message(STATUS "Found OpenCV version ${OpenCV_VERSION}")
else()
    message(FATAL_ERROR "OpenCV not found")
endif()
