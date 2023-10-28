cmake_minimum_required(VERSION 3.22)
project(rt CXX)

include_directories(
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(external)
add_subdirectory(src)