cmake_minimum_required(VERSION 2.8.8)
project(RAYTRACER)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 --std=c++11 -g")


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


add_subdirectory(projects)
