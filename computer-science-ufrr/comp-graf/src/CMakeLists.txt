
add_subdirectory(array)
add_subdirectory(rasterization)
add_subdirectory(fill)

add_executable(trab_2 main.cpp)

set(SFML_VERSION "2.6.0")

FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        "${SFML_VERSION}"
)


FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

target_compile_options(trab_2 PRIVATE -Wall)

target_link_libraries(trab_2
    PUBLIC
        array
        rasterization
        fill
    PRIVATE
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window
)
