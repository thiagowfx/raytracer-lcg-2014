add_executable (runRaytracer main.cpp ${RAYTRACER_SOURCES} ${PCS_DETECTION_DIR}/qwqw.cpp)
# alt: add_executable (runRaytracer main.cpp $<TARGET_OBJECTS:RAYTRACER_LIBRARY>)

target_link_libraries (runRaytracer ${PNG_LIBRARY})
