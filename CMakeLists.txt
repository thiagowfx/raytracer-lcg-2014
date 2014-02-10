cmake_minimum_required(VERSION 2.6)

# Project name: reference it like ${PROJECT_SOURCE_DIR} and ${PROJECT_BINARY_DIR}
project(RAYTRACER)
# set(CMAKE_CXX_FLAGS "-O2 -Wall") # release
set(CMAKE_CXX_FLAGS "-g -Wall") # debug

# include directories
include_directories(/usr/include/eigen3)

# include libraries
find_package(PNG REQUIRED)	# PNGPP/libPNG

# Manually include subdirs
# set(SUBDIRS Build GeometricObjects Main Tracers UserInterface Utilities World)
# FOREACH(subdir ${SUBDIRS})
#   ADD_SUBDIRECTORY(${subdir})
# ENDFOREACH()

# include all .cpp and .h files from the src/ dir
file(GLOB_RECURSE RAYTRACER_SOURCES "src/*.cpp")
file(GLOB_RECURSE RAYTRACER_HEADERS "src/*.h")

# include dirs which contain those files
set (RAYTRACER_INCLUDE_DIRS "")
foreach (_headerFile ${RAYTRACER_HEADERS} ${RAYTRACER_SOURCES})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND RAYTRACER_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES RAYTRACER_INCLUDE_DIRS)
include_directories(${RAYTRACER_INCLUDE_DIRS})

# executable and file dependencies
add_executable (raytracerBin ${RAYTRACER_SOURCES})

# library dependencies
target_link_libraries (raytracerBin ${PNG_LIBRARY})
