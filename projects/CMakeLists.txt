find_package(PNG REQUIRED)
include_directories(/usr/include/eigen3)


# do NOT change this order
add_subdirectory(pcs-detection)
add_subdirectory(raytracer)

include_directories(${RAYTRACER_INCLUDE_DIRS})
include_directories(${PCS_DETECTION_INCLUDE_DIRS})


add_executable(
  runRaytracer
  main.cpp
  $<TARGET_OBJECTS:RAYTRACER_LIBRARY>
  $<TARGET_OBJECTS:PCS_DETECTION_LIBRARY>
  )

target_link_libraries(
  runRaytracer
  ${PNG_LIBRARY}
  )
