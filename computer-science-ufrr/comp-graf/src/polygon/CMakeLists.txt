add_library(Polygon Polygon.cpp Polygon.hpp)

target_include_directories(Polygon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Polygon array2d rasterization)