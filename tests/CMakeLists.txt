##################################################
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


##################################################
# Executable
# add_executable(runTests tests.cpp ${RAYTRACER_SOURCES})
add_executable(runTests tests.cpp $<TARGET_OBJECTS:RAYTRACER_LIBRARY>)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ${PNG_LIBRARY})


##################################################
# CTest integration (optional, to run it with `ctest`)
add_test(runTests runTests)
