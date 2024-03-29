cmake_minimum_required(VERSION 2.8.12)

# Project declaration
project(HOPE)
set(CMAKE_HOME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib/${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# List source files
file (
    GLOB_RECURSE
    SOURCES
    ${CMAKE_HOME_DIRECTORY}/src/*.cpp
)

# Set the include files for the library.
include_directories (
    ${DOOM_INCLUDE_DIRS}
    ${MIND_INCLUDE_DIRS}
    ${SPITE_INCLUDE_DIRS}
    ${CMAKE_HOME_DIRECTORY}/include
)

# Generate the output library
add_library (
    ${PROJECT_NAME}
    SHARED
    ${SOURCES}
)

# Linux/Windows dependencies
include("./dependencies.cmake")

target_link_libraries(${PROJECT_NAME} DOOM MIND SPITE)

# Versioning
if (UNIX)
    if(DEBUG)
        list(APPEND CMAKE_CXX_FLAGS "-W -Wall -Werror -std=c++20 -g ${CMAKE_CXX_FLAGS}")
    else()
        list(APPEND CMAKE_CXX_FLAGS "-O3 -W -Wall -Werror -std=c++20 ${CMAKE_CXX_FLAGS}")
    endif()

    set(HOPE_VERSION_MAJOR 0)
    set(HOPE_VERSION_MINOR 2)
    set(HOPE_VERSION_PATCH 0)
    set(HOPE_VERSION_STRING ${HOPE_VERSION_MAJOR}.${HOPE_VERSION_MINOR}.${HOPE_VERSION_PATCH})

    set_target_properties (
        ${PROJECT_NAME}
        PROPERTIES
        VERSION ${HOPE_VERSION_STRING}
        SOVERSION ${HOPE_VERSION_MAJOR}
    )
endif()

set (
    ${PROJECT_NAME}_DEFINITIONS
    CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE
)

set (
    ${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_HOME_DIRECTORY}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)
