##################################################
# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")


##################################################
# -I flag
include_directories(${RAYTRACER_INCLUDE_DIRS})


##################################################
# Executables
add_executable (RAYTRACER_BIN ${RAYTRACER_SOURCES})


##################################################
# -l flag (library dependencies)
target_link_libraries (RAYTRACER_BIN ${PNG_LIBRARY})
