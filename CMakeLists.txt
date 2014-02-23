cmake_minimum_required(VERSION 2.6)

project(RAYTRACER)

##################################################
# Dependencies
find_package(PNG REQUIRED)	# pngpp / png++ / libPNG
include_directories(/usr/include/eigen3)


##################################################
# Subdirectories
add_subdirectory(src)
