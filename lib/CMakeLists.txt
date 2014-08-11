########## DEPENDENCIES ##########

# libpng++-dev on Ubuntu, png++ (AUR) on Arch
find_package(PNG REQUIRED)

find_package(Boost REQUIRED COMPONENTS serialization)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Qt5Widgets REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# mesa3d on Intel and nvidia-driver on Nvidia graphic cards
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
endif()

include_directories(/usr/include/eigen3)

set(PCS_DETECTION_DIR "${CMAKE_CURRENT_SOURCE_DIR}/pcs-detection/pcs-detection")
set(VCG_DIR "${PCS_DETECTION_DIR}/../vcglib")
set(RAYTRACER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/raytracer")

########## PCS_DETECTION ##########
include_directories(${PCS_DETECTION_DIR})
include_directories(${VCG_DIR})
file(
  GLOB
  PCS_DETECTION_SOURCES
  "${PCS_DETECTION_DIR}/cone.cpp"
  "${PCS_DETECTION_DIR}/cylinder.cpp"
  "${PCS_DETECTION_DIR}/kdtree.cpp"
  "${PCS_DETECTION_DIR}/invertedcylinder.cpp"
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
  "${PCS_DETECTION_DIR}/invertedcylinder.h"
  "${PCS_DETECTION_DIR}/pc-shape-detection.h"
  "${PCS_DETECTION_DIR}/pcsmath.h"
  "${PCS_DETECTION_DIR}/plane.h"
  "${PCS_DETECTION_DIR}/primitive.h"
  "${PCS_DETECTION_DIR}/shape.h"
  "${PCS_DETECTION_DIR}/sphere.h"
  "${PCS_DETECTION_DIR}/torus.h"
  "${PCS_DETECTION_DIR}/tree.h"
  )
file(
  GLOB
  VCG_SOURCES
  "${VCG_DIR}/wrap/ply/plylib.cpp"
  )

add_library(PCS_DETECTION_LIBRARY OBJECT ${PCS_DETECTION_SOURCES})

########## RAYTRACER ##########
file(
  GLOB
  RAYTRACER_INCLUDE_DIRS
  "${RAYTRACER_DIR}/BRDFs"
  "${RAYTRACER_DIR}/GeometricObjects"
  "${RAYTRACER_DIR}/Lights"
  "${RAYTRACER_DIR}/Materials"
  "${RAYTRACER_DIR}/Samplers"
  "${RAYTRACER_DIR}/Tracers"
  "${RAYTRACER_DIR}/World"
  )
include_directories(${RAYTRACER_INCLUDE_DIRS})

file(GLOB_RECURSE RAYTRACER_SOURCES "${RAYTRACER_DIR}/*.cpp")
file(GLOB_RECURSE RAYTRACER_HEADERS "${RAYTRACER_DIR}/*.h" "${RAYTRACER_DIR}/*.hpp")

add_library(RAYTRACER_LIBRARY OBJECT ${RAYTRACER_SOURCES})

########## MAIN ##########
set(QT_RAYTRACER qtraytracer)

qt5_wrap_ui(
  QT_UIS
  mainwindow.ui
  )

qt5_add_resources(
  QT_RCCS
  resources.qrc
  )

file(
  GLOB
  QT_RAYTRACER_SOURCES
  "mainwindow.cpp"
  "mainwindow.h"
  "main_qt.cpp"
  "RaytracerApi.cpp"
  "RaytracerApi.h"
  )

add_executable(
  ${QT_RAYTRACER}
  ${QT_RAYTRACER_SOURCES}
  ${QT_UIS}
  ${QT_RCCS}
  ${VCG_SOURCES}
  $<TARGET_OBJECTS:RAYTRACER_LIBRARY>
  $<TARGET_OBJECTS:PCS_DETECTION_LIBRARY>
  )

target_link_libraries(
  ${QT_RAYTRACER}
  ${Boost_LIBRARIES}
  ${PNG_LIBRARY}
  ${OPENGL_LIBRARIES}
  Qt5::Widgets
  )

########## DOCUMENTATION ##########
add_custom_target(docs
  COMMAND doxygen "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
  COMMENT "Generate the doxygen documentation."
  )


########## TESTS ##########

# Taken from: https://github.com/dmonopoly/gtest-cmake-example/blob/master/CMakeLists.txt
# Options. Turn on with 'cmake -DTEST=ON ..'.

# Makes boolean 'test' available.
option(TEST "Build all tests." OFF)

if (TEST)
  find_package(GTest REQUIRED)
  enable_testing()

  # Include the gtest library.
  include_directories($GTEST_INCLUDE_DIRS)

  # Unit Tests
  add_executable(
    serializationTests
    tests/serialization_tests.cpp
    ${VCG_SOURCES}
    $<TARGET_OBJECTS:RAYTRACER_LIBRARY>
    $<TARGET_OBJECTS:PCS_DETECTION_LIBRARY>
    )

  # Standard linking to gtest stuff.
  target_link_libraries(
    serializationTests
    ${Boost_LIBRARIES}
    ${GTEST_LIBRARIES}
    ${PNG_LIBRARY}
    ${OPENGL_LIBRARIES}
    )

  # Use this for each test executable.
  add_test(test serializationTests)

  add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} -V
    COMMENT "This way you can run 'make check' to execute tests."
    )
endif()
