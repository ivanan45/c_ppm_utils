cmake_minimum_required(VERSION 3.10)

project(c_ppm_utils C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(viewer viewer.c ppm.c)
add_executable(writer writer.c ppm.c)

target_link_libraries(viewer PRIVATE SDL2::SDL2)
