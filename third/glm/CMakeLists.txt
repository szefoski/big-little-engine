cmake_minimum_required(VERSION 3.0)
project(GlmGit)

include(FetchContent)

FetchContent_Declare(
  glm_git
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        0.9.9.8
  GIT_PROGRESS   TRUE
  USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_GetProperties(glm_git)
if(NOT glm_git_POPULATED)
  FetchContent_Populate(glm_git)
  add_subdirectory(${glm_git_SOURCE_DIR} build)
endif()