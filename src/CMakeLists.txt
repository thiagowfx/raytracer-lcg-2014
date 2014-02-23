##################################################
# Variables
file(GLOB_RECURSE RAYTRACER_SOURCES "*.cpp")
file(GLOB_RECURSE RAYTRACER_HEADERS "*.h")

# include the directories which contain those files
set (RAYTRACER_INCLUDE_DIRS "")
foreach (_headerFile ${RAYTRACER_HEADERS} ${RAYTRACER_SOURCES})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND RAYTRACER_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES RAYTRACER_INCLUDE_DIRS)


##################################################
# Rules

set(CMAKE_CXX_FLAGS "-g -O2 -Wall -Wextra")

# -I
include_directories(${RAYTRACER_INCLUDE_DIRS})

# Ray tracer executable
add_executable (raytracerBin ${RAYTRACER_SOURCES} ${RAYTRACER_HEADERS})

# -l (library dependencies)
target_link_libraries (raytracerBin ${PNG_LIBRARY})
