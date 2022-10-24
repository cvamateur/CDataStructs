cmake_minimum_required(VERSION 3.23)
project(CDataStructs C)

set(CMAKE_C_STANDARD 11)

file(GLOB srcs LIST_DIRECTORIES false "src/*.c")
message("Found srcs: ${srcs}")
add_library(ds SHARED ${srcs})
target_include_directories(ds PRIVATE ./include)


macro(add_test name)
    add_executable(test_${name} tests/test_${name}.c)
    message("-- Add test: test_${name}")
    target_include_directories(test_${name} PRIVATE include)
    target_link_libraries(test_${name} PRIVATE ds)
endmacro()

add_test(vector)
add_test(list)