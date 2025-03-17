# Add subdirectories for dependencies
add_subdirectory(array2d)
add_subdirectory(rasterization)
add_subdirectory(fill)
add_subdirectory(geometric)
add_subdirectory(curve)

# Define the executable
add_executable(trab_2 main.cpp)

# Enable compiler warnings
target_compile_options(trab_2 PRIVATE -Wall)

# Link libraries, including OpenCV
target_link_libraries(trab_2
    PUBLIC
        array2d
        rasterization
        fill
        geometric
        curve
    PRIVATE
        ${OpenCV_LIBS}  # Use OpenCV-provided libraries
)

# Include OpenCV headers
target_include_directories(trab_2 PRIVATE ${OpenCV_INCLUDE_DIRS})