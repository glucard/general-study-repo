add_library(fill fill.cpp fill.hpp)

target_include_directories(fill PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(fill array2d)