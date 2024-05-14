add_subdirectory(3d)
add_subdirectory(engine)
add_subdirectory(graphics)
add_subdirectory(logger)
add_subdirectory(resource_loader)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    main.cpp
)