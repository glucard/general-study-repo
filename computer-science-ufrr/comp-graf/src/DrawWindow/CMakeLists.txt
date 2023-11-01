add_library(DrawWindow DrawWindow.cpp DrawWindow.hpp)

target_include_directories(DrawWindow PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(DrawWindow
    PUBLIC
        array2d
        rasterization
        fill
        polygon
    PRIVATE
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window
)
