cmake_minimum_required(VERSION 3.0)
project(GlfwGit)

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
set( GLFW_INSTALL OFF CACHE BOOL "" FORCE )

include(FetchContent)

set(PROJECT_DOWNLOAD_NAME glfw_git)

FetchContent_Declare(
  ${PROJECT_DOWNLOAD_NAME}
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.2
  GIT_PROGRESS   TRUE
  USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_GetProperties(${PROJECT_DOWNLOAD_NAME})
if(NOT ${PROJECT_DOWNLOAD_NAME}_POPULATED)
  FetchContent_Populate(${PROJECT_DOWNLOAD_NAME})
  add_subdirectory(${${PROJECT_DOWNLOAD_NAME}_SOURCE_DIR} build)
endif()