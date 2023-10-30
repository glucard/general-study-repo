add_library(rasterization
    CircumferenceRasterization.cpp LineRasterization.cpp
    CircumferenceRasterization.hpp LineRasterization.hpp
)

target_include_directories(rasterization PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rasterization array)