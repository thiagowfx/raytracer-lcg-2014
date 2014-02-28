##################################################
# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")


##################################################
# Executables
add_library(RAYTRACER_LIBRARY OBJECT ${RAYTRACER_SOURCES})
# add_executable (runRayTracer main.cpp ${RAYTRACER_SOURCES})
add_executable (runRaytracer main.cpp $<TARGET_OBJECTS:RAYTRACER_LIBRARY>)


##################################################
# -l flag (library dependencies)
target_link_libraries (runRaytracer ${PNG_LIBRARY})
