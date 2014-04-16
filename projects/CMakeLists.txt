find_package(PNG REQUIRED)
include_directories(/usr/include/eigen3)
include_directories(pcs-detection/vcglib)


# do NOT change this order
add_subdirectory(pcs-detection)
add_subdirectory(raytracer)

include_directories(${RAYTRACER_INCLUDE_DIRS})
include_directories(${PCS_DETECTION_INCLUDE_DIRS})


# Qt Build
# See http://qt-project.org/doc/qt-5/cmake-manual.html

set(QT_RAYTRACER qtRaytracer)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Qt 4
# https://qt-project.org/quarterly/view/using_cmake_to_build_qt_projects
############################################################
find_package(Qt)

qt4_wrap_ui(
  ${QT_RAYTRACER}_UIC
  mainwindow.ui
  )

qt4_add_resources(
  ${QT_RAYTRACER}_RCC
  resources.qrc
  )

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_executable(
  ${QT_RAYTRACER}
  main_qt.cpp
  mainwindow.cpp
  $<TARGET_OBJECTS:RAYTRACER_LIBRARY>
  $<TARGET_OBJECTS:PCS_DETECTION_LIBRARY>
  ${${QT_RAYTRACER}_UIC}
  ${${QT_RAYTRACER}_RCC}
  )

target_link_libraries(
  ${QT_RAYTRACER}
  ${PNG_LIBRARY}
  ${QT_LIBRARIES}
  )

# Qt 5
# http://qt-project.org/doc/qt-5/cmake-manual.html
############################################################
# Find the QtWidgets library
# find_package(Qt5Widgets REQUIRED)


# # http://www.itk.org/pipermail/insight-users/2009-October/032974.html
# qt5_wrap_ui(
#   ${QT_RAYTRACER}_UIC
#   mainwindow.ui
#   )

# qt5_add_resources(
#   ${QT_RAYTRACER}_RCC
#   resources.qrc
#   )
  
# add_executable(
#   ${QT_RAYTRACER}
#   main_qt.cpp
#   mainwindow.cpp
#   $<TARGET_OBJECTS:RAYTRACER_LIBRARY>
#   $<TARGET_OBJECTS:PCS_DETECTION_LIBRARY>
#   ${${QT_RAYTRACER}_UIC}
#   ${${QT_RAYTRACER}_RCC}
#   )

# qt5_use_modules(
#   ${QT_RAYTRACER}  
#   Widgets
#   )

# target_link_libraries(
#   ${QT_RAYTRACER}
#   ${PNG_LIBRARY}
#   )
