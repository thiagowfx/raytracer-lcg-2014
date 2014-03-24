##################################################
# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")


##################################################
# Executables
add_library(RAYTRACER_LIBRARY OBJECT ${RAYTRACER_SOURCES}) # for tests
add_executable (runRaytracer main.cpp ${RAYTRACER_SOURCES})
# alt:
# add_executable (runRaytracer main.cpp $<TARGET_OBJECTS:RAYTRACER_LIBRARY>)


##################################################
# library dependencies
target_link_libraries (runRaytracer ${PNG_LIBRARY})
