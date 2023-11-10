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
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/blinn-phong.frag
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/blinn-phong.vert
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad glfw glm)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# Visual Studio stuff
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES USE_FOLDERS ON)
get_target_property(RT_SOURCES ${CMAKE_PROJECT_NAME} SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${RT_SOURCES})

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shaders $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/resources/shaders
)