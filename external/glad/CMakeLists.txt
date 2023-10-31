project(glad)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)