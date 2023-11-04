add_executable(${CMAKE_PROJECT_NAME})

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/external/glad/include
        ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(engine)
add_subdirectory(glContext)
add_subdirectory(utils)
add_subdirectory(object)
add_subdirectory(scene)
add_subdirectory(window)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad glfw glm)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# Visual Studio stuff
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES USE_FOLDERS ON)
get_target_property(RT_SOURCES ${CMAKE_PROJECT_NAME} SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${RT_SOURCES})
