cmake_minimum_required(VERSION 2.6)
project(RAYTRACER)

enable_testing()

find_package(PNG REQUIRED)	# pngpp / png++ / libPNG
include_directories(/usr/include/eigen3)


file(GLOB_RECURSE RAYTRACER_SOURCES "src/*.cpp")
file(GLOB_RECURSE RAYTRACER_HEADERS "src/*.h")

# include directories which contain these files
set (RAYTRACER_INCLUDE_DIRS "")
foreach (_headerFile ${RAYTRACER_HEADERS} ${RAYTRACER_SOURCES})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND RAYTRACER_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES RAYTRACER_INCLUDE_DIRS)


add_subdirectory(src)
add_subdirectory(tests)
