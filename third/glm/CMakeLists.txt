cmake_minimum_required(VERSION 3.0)
project(GlmGit)

include(FetchContent)

set(PROJECT_DOWNLOAD_NAME glm_git)

FetchContent_Declare(
  ${PROJECT_DOWNLOAD_NAME}
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        0.9.9.8
  GIT_PROGRESS   TRUE
  USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_GetProperties(${PROJECT_DOWNLOAD_NAME})
if(NOT ${PROJECT_DOWNLOAD_NAME}_POPULATED)
  FetchContent_Populate(${PROJECT_DOWNLOAD_NAME})
  add_subdirectory(${${PROJECT_DOWNLOAD_NAME}_SOURCE_DIR} build)
endif()