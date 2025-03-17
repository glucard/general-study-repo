# Create the array2d library
add_library(array2d array2d.cpp array2d.hpp)

# Include directories for array2d
target_include_directories(array2d 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # Include the current source directory
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}  # Include OpenCV header files (PRIVATE because it's used only internally)
)

# Link OpenCV to the array2d library
target_link_libraries(array2d
    PRIVATE
        ${OpenCV_LIBS}  # Link OpenCV libraries to array2d
)
