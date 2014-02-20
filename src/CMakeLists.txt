set(CMAKE_CXX_FLAGS "-g -O2 -Wall")

include_directories(${RAYTRACER_INCLUDE_DIRS})

add_executable (raytracerBin ${RAYTRACER_SOURCES} ${RAYTRACER_HEADERS})
target_link_libraries (raytracerBin ${PNG_LIBRARY})
