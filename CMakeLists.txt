# CMakeList.txt : CMake project for Test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Tinyexp")

add_library(Tinyexp "tinyexpr.c" "tinyexpr.h" "example_logic.c")

add_executable(Example example.c)
add_executable(Example_logic "example_logic.c")

target_include_directories(Example PUBLIC .)
target_link_libraries(Example Tinyexp)
target_link_libraries(Example_logic Tinyexp)
