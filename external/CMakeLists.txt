# add_subdirectory(glad)

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
  FIND_PACKAGE_ARGS NAMES glfw3
)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
)

FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG        master
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
)

FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        glad2
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(glad)
if (NOT glad_POPULATED)
  FetchContent_Populate(glad)
  add_subdirectory(${glad_SOURCE_DIR}/cmake ${glad_BINARY_DIR})
  glad_add_library(glad STATIC REPRODUCIBLE LOADER LANGUAGE C API gl:core=4.6)
endif()

FetchContent_GetProperties(stb)
if (NOT stb_POPULATED)
  FetchContent_Populate(stb)
  target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${stb_SOURCE_DIR})
endif()

FetchContent_MakeAvailable(glfw glm glad stb)