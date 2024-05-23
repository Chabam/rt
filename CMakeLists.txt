cmake_minimum_required(VERSION 3.22)

project(rt)

add_subdirectory(external)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(src)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad glfw glm)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

if (CMAKE_GENERATOR MATCHES "Visual Studio*")
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES USE_FOLDERS ON)
    get_target_property(RT_SOURCES ${CMAKE_PROJECT_NAME} SOURCES)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${RT_SOURCES})
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/resources
)