find_package(PNG REQUIRED)
include_directories(/usr/include/eigen3)

########## PCS_DETECTION ##########
set(PCS_DETECTION_DIR "${CMAKE_CURRENT_SOURCE_DIR}/pcs-detection/pcs-detection")
set(PCS_DETECTION_INCLUDE_DIRS "${PCS_DETECTION_DIR}")
file(
  GLOB
  PCS_DETECTION_SOURCES
  "${PCS_DETECTION_DIR}/cone.cpp"
  "${PCS_DETECTION_DIR}/cylinder.cpp"
  "${PCS_DETECTION_DIR}/kdtree.cpp"
  "${PCS_DETECTION_DIR}/pcsmath.cpp"
  "${PCS_DETECTION_DIR}/plane.cpp"
  "${PCS_DETECTION_DIR}/primitive.cpp"
  "${PCS_DETECTION_DIR}/shape.cpp"
  "${PCS_DETECTION_DIR}/sphere.cpp"
  "${PCS_DETECTION_DIR}/torus.cpp"
  "${PCS_DETECTION_DIR}/tree.cpp"
  )
file(
  GLOB
  PCS_DETECTION_HEADERS
  "${PCS_DETECTION_DIR}/cone.h"
  "${PCS_DETECTION_DIR}/cylinder.h"
  "${PCS_DETECTION_DIR}/kdtree.h"
  "${PCS_DETECTION_DIR}/pc-shape-detection.h"
  "${PCS_DETECTION_DIR}/pcsmath.h"
  "${PCS_DETECTION_DIR}/plane.h"
  "${PCS_DETECTION_DIR}/primitive.h"
  "${PCS_DETECTION_DIR}/shape.h"
  "${PCS_DETECTION_DIR}/sphere.h"
  "${PCS_DETECTION_DIR}/torus.h"
  "${PCS_DETECTION_DIR}/tree.h"
  )

include_directories(${PCS_DETECTION_INCLUDE_DIRS})
include_directories(${PCS_DETECTION_INCLUDE_DIRS}/../vcglib)
add_library(PCS_DETECTION_LIBRARY OBJECT ${PCS_DETECTION_SOURCES})


########## RAYTRACER ##########
set(RAYTRACER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/raytracer")
file(
  GLOB
  RAYTRACER_INCLUDE_DIRS
  "${RAYTRACER_DIR}"
  "${RAYTRACER_DIR}/BRDFs"
  "${RAYTRACER_DIR}/Cameras"
  "${RAYTRACER_DIR}/GeometricObjects"
  "${RAYTRACER_DIR}/Lights"
  "${RAYTRACER_DIR}/Materials"
  "${RAYTRACER_DIR}/Samplers"
  "${RAYTRACER_DIR}/Tracers"
  "${RAYTRACER_DIR}/Utilities"
  "${RAYTRACER_DIR}/World"
  )
file(GLOB_RECURSE RAYTRACER_SOURCES "${RAYTRACER_DIR}/*.cpp")
file(GLOB_RECURSE RAYTRACER_HEADERS "${RAYTRACER_DIR}/*.h")

include_directories(${RAYTRACER_INCLUDE_DIRS})
add_library(RAYTRACER_LIBRARY OBJECT ${RAYTRACER_SOURCES})


########## MAIN ##########

set(QT_RAYTRACER qtRaytracer)
find_package(Qt5Widgets REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(
  QT_UIS
  mainwindow.ui
  )

qt5_add_resources(
  QT_RCCS
  resources.qrc
  )

add_executable(
  ${QT_RAYTRACER}
  mainwindow.cpp
  mainwindow.h
  main_qt.cpp
  includes.h
  RaytracerApi.cpp
  RaytracerApi.h
  $<TARGET_OBJECTS:RAYTRACER_LIBRARY>
  $<TARGET_OBJECTS:PCS_DETECTION_LIBRARY>
  ${QT_UIS}
  ${QT_RCCS}
  )

qt5_use_modules(
  ${QT_RAYTRACER}
  Widgets
  )

target_link_libraries(
  ${QT_RAYTRACER}
  ${PNG_LIBRARY}
  )

########## DOCUMENTATION ##########
add_custom_target(doc
  COMMAND doxygen "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
  COMMENT "Generate documentation."
  )
