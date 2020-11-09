cmake_minimum_required(VERSION 3.0)
project(GladGit)

include(FetchContent)

set(PROJECT_DOWNLOAD_NAME glad_git)

FetchContent_Declare(
  ${PROJECT_DOWNLOAD_NAME}
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        1d7b6e9e908e32e3237caad55836134af92a32f6
  GIT_PROGRESS   TRUE
  USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_GetProperties(${PROJECT_DOWNLOAD_NAME})
if(NOT ${PROJECT_DOWNLOAD_NAME}_POPULATED)
  FetchContent_Populate(${PROJECT_DOWNLOAD_NAME})
  add_subdirectory(${${PROJECT_DOWNLOAD_NAME}_SOURCE_DIR}/cmake build)

  set( GLAD_GEN_DIR ${FETCHCONTENT_BASE_DIR}/glad_gen CACHE STRING "" )
  glad_add_library(glad_build REPRODUCIBLE API gl:core=4.6 LOCATION ${GLAD_GEN_DIR})
endif()