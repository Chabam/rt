add_subdirectory(camera)
add_subdirectory(geometries)
add_subdirectory(light)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    material.h
    material.cpp
    mesh.h
    mesh.cpp
    object3d.h
    object3d.cpp
)