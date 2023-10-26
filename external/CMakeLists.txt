add_subdirectory(glad)

include(FetchContent)

FetchContent_Declare(
  GLFW
  GIT_REPOSITORY https://github.com/glfw/glfw.git
)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
)
FetchContent_MakeAvailable(GLFW glm)

include_directories(
  ${GLFW_SOURCE_DIR}/include
  ${glm_SOURCE_DIR}
  )