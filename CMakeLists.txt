cmake_minimum_required(VERSION 3.16)
project(math_ops C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(MATH_OPS_SOURCES
    src/mo_common.c
    src/mo_scalar.c
    src/mo_matrix.c
    src/mo_memory.c
)

add_library(math_ops SHARED ${MATH_OPS_SOURCES})
target_include_directories(
    math_ops
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(WIN32)
    target_compile_definitions(math_ops PRIVATE MO_BUILD_DLL)
endif()

add_executable(math_ops_demo examples/demo.c)
target_link_libraries(math_ops_demo PRIVATE math_ops)

add_executable(math_ops_c_tests tests/test_math_ops_c.c)
target_link_libraries(math_ops_c_tests PRIVATE math_ops)

enable_testing()
add_test(NAME math_ops_c_tests COMMAND math_ops_c_tests)
