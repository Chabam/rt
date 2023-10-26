cmake_minimum_required(VERSION 3.26)

project(glad)

set(GLAD_INCLUDE_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(GLAD_SRC_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC
    ${GLAD_INCLUDE_DIR}/glad/gl.h
    ${GLAD_INCLUDE_DIR}/KHR/khrplatform.h
)

target_sources(${PROJECT_NAME} PRIVATE
    ${GLAD_SRC_DIR}/gl.c
)


target_include_directories(${PROJECT_NAME} PUBLIC ${GLAD_INCLUDE_DIR})