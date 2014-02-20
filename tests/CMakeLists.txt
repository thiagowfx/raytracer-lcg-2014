include_directories(${RAYTRACER_INCLUDE_DIRS})
find_package(Boost REQUIRED unit_test_framework)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-lboost_unit_test_framework")

# - Ray tracer
#   - https://stackoverflow.com/questions/15732329/error-linking-to-boost-filesystem-using-cmake-on-cygwin

# add_executable(testHelloWorld testHelloWorld.cpp)
add_executable(testRGBColor testRGBColor.cpp ../src/Utilities/RGBColor.cpp)


########################################
# Tests

# add_test(testHelloWorld testHelloWorld)
add_test(testRGBColor testRGBColor)
