add_library(BezierCurve BezierCurve.cpp BezierCurve.hpp)

target_include_directories(BezierCurve PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(BezierCurve array2d Polygon)