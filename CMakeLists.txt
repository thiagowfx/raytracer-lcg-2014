##################################################
# Metadata
cmake_minimum_required(VERSION 2.8.8)
project(RAYTRACER)


##################################################
# Helper Macros
# Returns to `result` a list with all subdirs of `curdir`. Absolute path!
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${child})
        SET(dirlist ${dirlist} ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()


##################################################
# Variables
file(GLOB_RECURSE RAYTRACER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE RAYTRACER_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
subdirlist(RAYTRACER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Remove main.cpp from sources
list(REMOVE_ITEM RAYTRACER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)


##################################################
# Dependencies
find_package(PNG REQUIRED)	# pngpp / png++ / libPNG
include_directories(/usr/include/eigen3)
include_directories(${RAYTRACER_INCLUDE_DIRS})


##################################################
# Subdirectories
add_subdirectory(src)


##################################################
# Tests - use `cmake .. -DTEST=ON` to enable tests.
if(TEST)
  enable_testing()
  add_subdirectory(tests)
endif()
