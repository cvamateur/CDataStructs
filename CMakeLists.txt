cmake_minimum_required(VERSION 3.23)
project(CDataStructs C)

set(CMAKE_C_STANDARD 11)


include_directories(./include)

# compile utils
file(GLOB srcs LIST_DIRECTORIES false "src/utils/*.c")
message("Found srcs: ${srcs}")
add_library(common SHARED ${srcs})

# compile datastructures
file(GLOB srcs LIST_DIRECTORIES false "src/cds/*.c")
message("Found srcs: ${srcs}")
add_library(cds SHARED ${srcs})
target_link_libraries(cds PRIVATE common)

# compile sorting
file(GLOB srcs LIST_DIRECTORIES false "src/sorting/*.c")
message("Found srcs: ${srcs}")
add_library(csort SHARED ${srcs})
target_link_libraries(csort PRIVATE common)

macro(add_test name)
    add_executable(test_${name} tests/test_${name}.c)
    message("-- Add test: test_${name}")
    target_include_directories(test_${name} PRIVATE include)
    target_link_libraries(test_${name} PRIVATE common cds csort)
endmacro()

add_test(vector)
add_test(list)
add_test(stack)
add_test(queue)
add_test(btree)
add_test(deque)
