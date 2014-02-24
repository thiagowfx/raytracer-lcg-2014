##################################################
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


##################################################
# Executable
add_executable(runTests hello.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
