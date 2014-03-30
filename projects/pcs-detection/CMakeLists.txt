# PCS_DETECTION
set(PCS_DETECTION_DIR "${CMAKE_CURRENT_SOURCE_DIR}/pcs-detection")
set(PCS_DETECTION_INCLUDE_DIRS "${PCS_DETECTION_DIR}" PARENT_SCOPE)

file(
  GLOB
  PCS_DETECTION_SOURCES
  "${PCS_DETECTION_DIR}/cone.cpp"
  "${PCS_DETECTION_DIR}/cylynder.cpp"
  "${PCS_DETECTION_DIR}/kdtree.cpp"
  "${PCS_DETECTION_DIR}/pcsmath.cpp"
  "${PCS_DETECTION_DIR}/plane.cpp"
  "${PCS_DETECTION_DIR}/primitive.cpp"
  "${PCS_DETECTION_DIR}/shape.cpp"
  "${PCS_DETECTION_DIR}/sphere.cpp"
  "${PCS_DETECTION_DIR}/torus.cpp"
  "${PCS_DETECTION_DIR}/tree.cpp"
  "${PCS_DETECTION_DIR}/qwqw.cpp"
  )
file(
  GLOB
  PCS_DETECTION_HEADERS
  "${PCS_DETECTION_DIR}/cone.h"
  "${PCS_DETECTION_DIR}/cylynder.h"
  "${PCS_DETECTION_DIR}/glwidget.h"
  "${PCS_DETECTION_DIR}/kdtree.h"
  "${PCS_DETECTION_DIR}/octree.h"
  "${PCS_DETECTION_DIR}/pc-shape-detection.h"
  "${PCS_DETECTION_DIR}/pcsmath.h"
  "${PCS_DETECTION_DIR}/plane.h"
  "${PCS_DETECTION_DIR}/primitive.h"
  "${PCS_DETECTION_DIR}/shape.h"
  "${PCS_DETECTION_DIR}/sphere.h"
  "${PCS_DETECTION_DIR}/torus.h"
  "${PCS_DETECTION_DIR}/tree.h"
  "${PCS_DETECTION_DIR}/qwqw.h"
  )

include_directories(${PCS_DETECTION_INCLUDE_DIRS})
include_directories(vcglib)

add_library(PCS_DETECTION_LIBRARY OBJECT ${PCS_DETECTION_SOURCES})
