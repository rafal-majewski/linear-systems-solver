cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)

project(linear-systems-solver)


add_subdirectory(./src)
add_subdirectory(./lib)

enable_testing()
add_subdirectory(./tests)
