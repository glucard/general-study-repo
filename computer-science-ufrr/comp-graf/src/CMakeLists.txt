
add_subdirectory(array)
add_subdirectory(rasterization)

add_executable(trab_2 main.cpp)

target_link_libraries(trab_2
                        array
                        rasterization
)