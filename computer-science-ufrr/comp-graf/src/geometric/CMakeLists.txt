add_library(geometric
    Polygon.cpp Point.cpp
    Polygon.hpp Point.hpp)

# Include directories for array2d
target_include_directories(geometric 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # Include the current source directory
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}  # Include OpenCV header files (PRIVATE because it's used only internally)
)

# Link OpenCV to the array2d library
target_link_libraries(geometric
    PUBLIC
        array2d
        rasterization
    PRIVATE
        ${OpenCV_LIBS}  # Link OpenCV libraries to array2d
)
