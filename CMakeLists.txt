cmake_minimum_required(VERSION 2.6)

project(RAYTRACER)
set(CMAKE_CXX_FLAGS "-O3 -Wall")
find_package(PNG REQUIRED)

# set(SUBDIRS Build GeometricObjects Main Tracers UserInterface Utilities World)
# FOREACH(subdir ${SUBDIRS})
#   ADD_SUBDIRECTORY(${subdir})
# ENDFOREACH()

# include files
file(GLOB_RECURSE RAYTRACER_SOURCES "src/*.cpp")
file(GLOB_RECURSE RAYTRACER_HEADERS "src/*.h")

#include dirs
set (RAYTRACER_INCLUDE_DIRS "")
foreach (_headerFile ${RAYTRACER_HEADERS} ${RAYTRACER_SOURCES})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND RAYTRACER_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES RAYTRACER_INCLUDE_DIRS)
include_directories(${RAYTRACER_INCLUDE_DIRS})

# executable
add_executable (raytracerBin ${RAYTRACER_SOURCES})
target_link_libraries (raytracerBin ${PNG_LIBRARY})
