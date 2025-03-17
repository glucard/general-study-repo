add_library(curve 
    BelzierCurve.cpp BelzierCurve.hpp
)

# Include directories for array2d
target_include_directories(curve 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # Include the current source directory
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}  # Include OpenCV header files (PRIVATE because it's used only internally)
)

# Link OpenCV to the array2d library
target_link_libraries(curve
    PUBLIC
        array2d
        geometric
    PRIVATE
        ${OpenCV_LIBS}  # Link OpenCV libraries to array2d
)
