add_executable (
  runRaytracer
  main.cpp
  # ${RAYTRACER_SOURCES}
  $<TARGET_OBJECTS:RAYTRACER_LIBRARY>
  $<TARGET_OBJECTS:PCS_DETECTION_LIBRARY>
  )
# alt: add_executable (runRaytracer main.cpp $<TARGET_OBJECTS:RAYTRACER_LIBRARY>)

target_link_libraries (
  runRaytracer
  ${PNG_LIBRARY}
  )
