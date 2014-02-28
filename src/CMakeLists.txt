##################################################
# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")


##################################################
# Executables
add_executable (runRaytracer main.cpp ${RAYTRACER_SOURCES})


##################################################
# -l flag (library dependencies)
target_link_libraries (runRaytracer ${PNG_LIBRARY})
