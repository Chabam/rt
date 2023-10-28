project(glad)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PUBLIC
        include/glad/glad.h
        include/KHR/khrplatform.h
    PRIVATE
        src/glad.c
)
