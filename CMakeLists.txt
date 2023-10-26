cmake_minimum_required(VERSION 3.1)
project(rt CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(external)
add_subdirectory(src)