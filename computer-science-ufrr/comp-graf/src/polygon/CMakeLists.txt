add_library(polygon polygon.cpp polygon.hpp)

target_include_directories(polygon PUBLIC ${CMAKE_CURRRENT_SOURCE_DIR})

target_link_libraries(polygon array2d rasterization)