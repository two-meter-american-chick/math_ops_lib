cmake_minimum_required(VERSION 3.16)
project(math_ops C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(math_ops STATIC src/math_ops.c)
target_include_directories(math_ops PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(math_ops_demo examples/demo.c)
target_link_libraries(math_ops_demo PRIVATE math_ops)
