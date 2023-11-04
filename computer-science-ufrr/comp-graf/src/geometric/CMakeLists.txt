add_library(geometric
    Polygon.cpp Point.cpp
    Polygon.hpp Point.hpp)

target_include_directories(geometric PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(geometric array2d rasterization)