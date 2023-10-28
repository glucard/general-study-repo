cmake_minimum_required(VERSION 3.0.0)
project(trab_2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(array)
add_subdirectory(rasterization)

add_executable(trab_2 main.cpp)

target_link_libraries(trab_2
                        array
                        rasterization
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
