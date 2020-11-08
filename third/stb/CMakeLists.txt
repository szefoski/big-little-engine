cmake_minimum_required(VERSION 3.0)
project(StbGit)

include(FetchContent)

FetchContent_Declare(
  stb_git
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG        b42009b3b9d4ca35bc703f5310eedc74f584be58
  GIT_PROGRESS   TRUE
  USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_GetProperties(stb_git)
if(NOT stb_git_POPULATED)
  FetchContent_Populate(stb_git)
endif()

add_library(stb ${stb_git_SOURCE_DIR}/stb_image.h src/stb.cpp)

target_include_directories(stb PUBLIC ${stb_git_SOURCE_DIR})