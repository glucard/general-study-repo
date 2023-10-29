add_library(rasterization rasterization.cpp rasterization.hpp)

target_include_directories(rasterization PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rasterization array)