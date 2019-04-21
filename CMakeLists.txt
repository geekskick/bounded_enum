cmake_minimum_required(VERSION 3.14)
project(bounded_enums LANGUAGES CXX VERSION 0.0.1)

add_subdirectory(src)

enable_testing()
find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)
add_subdirectory(test)