add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(engine)
add_subdirectory(glContext)
add_subdirectory(logger)
add_subdirectory(object)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad GLFW glm)

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Werror)
