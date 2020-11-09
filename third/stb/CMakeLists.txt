cmake_minimum_required(VERSION 3.0)
project(StbGit)

include(FetchContent)

set(PROJECT_DOWNLOAD_NAME stb_git)

FetchContent_Declare(
  ${PROJECT_DOWNLOAD_NAME}
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG        b42009b3b9d4ca35bc703f5310eedc74f584be58
  GIT_PROGRESS   TRUE
  USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_GetProperties(${PROJECT_DOWNLOAD_NAME})
if(NOT ${PROJECT_DOWNLOAD_NAME}_POPULATED)
  FetchContent_Populate(${PROJECT_DOWNLOAD_NAME})
endif()

add_library(stb ${stb_git_SOURCE_DIR}/stb_image.h src/stb.cpp)
target_include_directories(stb PUBLIC ${stb_git_SOURCE_DIR})