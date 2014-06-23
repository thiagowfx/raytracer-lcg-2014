find_package(PNG REQUIRED)
include_directories(/usr/include/eigen3)

# pcs detection should come before raytracer
include_directories(pcs-detection/vcglib)
add_subdirectory(pcs-detection)
include_directories(${PCS_DETECTION_INCLUDE_DIRS})

add_subdirectory(raytracer)
include_directories(${RAYTRACER_INCLUDE_DIRS})

set(QT_RAYTRACER qtRaytracer)
find_package(Qt5Widgets REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(
  PROJECT_UIS
  mainwindow.ui
  )

qt5_add_resources(
  PROJECT_RCCS
  resources.qrc
  )

add_executable(
  ${QT_RAYTRACER}
  main_qt.cpp
  mainwindow.cpp
  Raytracer.cpp
  Raytracer.h
  $<TARGET_OBJECTS:RAYTRACER_LIBRARY>
  $<TARGET_OBJECTS:PCS_DETECTION_LIBRARY>
  ${PROJECT_UIS}
  ${PROJECT_RCCS}
  )

qt5_use_modules(
  ${QT_RAYTRACER}
  Widgets
  )

target_link_libraries(
  ${QT_RAYTRACER}
  ${PNG_LIBRARY}
  )
