##################################################
# Metadata
cmake_minimum_required(VERSION 2.8.8)
project(RAYTRACER)

# Tweaks
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")


##################################################
# Helper Macros
MACRO(SUBDIRLIST result curdir)
  # Returns to `result` a list with all subdirs of `curdir`. Absolute path!
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
# RAYTRACER
set(RAYTRACER_DIR "${CMAKE_SOURCE_DIR}/src")
subdirlist(RAYTRACER_INCLUDE_DIRS "${RAYTRACER_DIR}")
file(GLOB_RECURSE RAYTRACER_SOURCES "${RAYTRACER_DIR}/*.cpp")
list(REMOVE_ITEM RAYTRACER_SOURCES "${RAYTRACER_DIR}/main.cpp")
file(GLOB_RECURSE RAYTRACER_HEADERS "${RAYTRACER_DIR}/*.h")
add_library(RAYTRACER_LIBRARY ${RAYTRACER_SOURCES})

# PCS_DETECTION
set(PCS_DETECTION_DIR "${CMAKE_SOURCE_DIR}/third-party/pcs-detection")
set(PCS_DETECTION_INCLUDE_DIRS "${PCS_DETECTION_DIR}")
file(GLOB PCS_DETECTION_SOURCES "${PCS_DETECTION_DIR}/*.cpp")
file(GLOB PCS_DETECTION_HEADERS "${PCS_DETECTION_DIR}/*.h")
# add_library(PCS_DETECTION_LIBRARY ${PCS_DETECTION_SOURCES})


##################################################
# Dependencies
find_package(PNG REQUIRED)      # pngpp / png++ / libPNG
include_directories(/usr/include/eigen3)
include_directories(${RAYTRACER_INCLUDE_DIRS})
include_directories(${PCS_DETECTION_INCLUDE_DIRS})


##################################################
# Subdirectories
add_subdirectory(src)
add_subdirectory(third-party)


##################################################
# Tests - use `cmake .. -DTEST=ON` to enable tests.
if(TEST)
  enable_testing()
  add_subdirectory(tests)
endif()
