cmake_minimum_required(VERSION 3.0)
project(GlfwGit)

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
set( GLFW_INSTALL OFF CACHE BOOL "" FORCE )

include(FetchContent)

FetchContent_Declare(
  glfw_git
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.2
  GIT_PROGRESS   TRUE
  USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_GetProperties(glfw_git)
if(NOT glfw_git_POPULATED)
  FetchContent_Populate(glfw_git)
  set( GLFW_INCLUDE_DIR ${glfw_git_SOURCE_DIR}/include CACHE STRING "" )
  add_subdirectory(${glfw_git_SOURCE_DIR} build)
endif()