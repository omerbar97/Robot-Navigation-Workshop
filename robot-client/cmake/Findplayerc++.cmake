# Find playerc++ library and headers

find_package(PkgConfig REQUIRED)
pkg_check_modules(PLAYERCXX REQUIRED playerc++)

# Report results
if(PLAYERCXX_FOUND)
    set(PLAYERCXX_LIBRARIES ${PLAYERCXX_LIBRARIES})
    set(PLAYERCXX_INCLUDE_DIRS ${PLAYERCXX_INCLUDE_DIRS})
endif()
