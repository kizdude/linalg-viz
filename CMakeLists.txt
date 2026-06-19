cmake_minimum_required(VERSION 3.15)
project(linalg_viz C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ---- raylib (downloaded + built on first configure) ----
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)   # don't build raylib's examples
set(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5
)
FetchContent_MakeAvailable(raylib)

# ---- the linalg library (git submodule, built as a shared lib) ----
add_subdirectory(external/linalg)

# ---- the visualizer ----
add_executable(linalg_viz
    src/main.c
    src/scene_vectors.c
    src/scene_transform.c
    src/scene_eigen.c
)
target_include_directories(linalg_viz PRIVATE src)
target_link_libraries(linalg_viz PRIVATE raylib linalg)

if(NOT MSVC)
    target_compile_options(linalg_viz PRIVATE -Wall -Wextra)
endif()

# linalg is a shared library; copy its DLL next to the exe so it loads at runtime.
add_custom_command(TARGET linalg_viz POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:linalg> $<TARGET_FILE_DIR:linalg_viz>
    VERBATIM)
