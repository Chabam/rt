add_subdirectory(camera)
add_subdirectory(geometries)
add_subdirectory(materials)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    material.cpp
    mesh.cpp
    scene.cpp
)