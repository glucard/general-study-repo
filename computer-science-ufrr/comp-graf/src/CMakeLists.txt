
add_subdirectory(array2d)
add_subdirectory(rasterization)
add_subdirectory(fill)
add_subdirectory(geometric)
add_subdirectory(BezierCurve)

add_executable(trab_2 main.cpp)

target_compile_options(trab_2 PRIVATE -Wall)

target_link_libraries(trab_2
    PUBLIC
        array2d
        rasterization
        fill
        geometric
        BezierCurve
)
