cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(c_ppm_utils C)
add_executable(viewer viewer.c ppm.c)
add_executable(writer writer.c ppm.c)
