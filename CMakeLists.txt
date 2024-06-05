cmake_minimum_required(VERSION 3.22)

project(rt)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(external)

add_subdirectory(src)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad glfw glm)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include/)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:RT_DEBUG=1>)

if (UNIX)
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)
else()
    # Windows is a good software
    file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources RES_SRC)
    file(TO_NATIVE_PATH ${CMAKE_BINARY_DIR}/resources RES_DEST)
    execute_process(COMMAND cmd.exe /c mklink /j ${RES_DEST} ${RES_SRC})
endif()