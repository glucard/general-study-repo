cmake_minimum_required(VERSION 3.28)
project(trab_2Project VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Find OpenCV
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")


# Add the src directory
add_subdirectory(src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
