cmake_minimum_required(VERSION 3.0)
project(ImGui)

include(FetchContent)

set(PROJECT_DOWNLOAD_NAME imgui_git)

FetchContent_Declare(
  ${PROJECT_DOWNLOAD_NAME}
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG        b7530e5d04fcd9d5859c089244f562be82b4c531
  GIT_PROGRESS   TRUE
  USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_GetProperties(${PROJECT_DOWNLOAD_NAME})
if(NOT ${PROJECT_DOWNLOAD_NAME}_POPULATED)
  FetchContent_Populate(${PROJECT_DOWNLOAD_NAME})
endif()

add_library(imgui 
    ${imgui_git_SOURCE_DIR}/imgui.cpp
    ${imgui_git_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_git_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_git_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_git_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

add_dependencies(imgui glad_build glfw)
get_target_property(GLAD_BUILD_INCLUDES glad_build INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(GLFW_BUILD_INCLUDES glfw INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(imgui PUBLIC ${imgui_git_SOURCE_DIR} PRIVATE ${GLAD_BUILD_INCLUDES} ${GLFW_BUILD_INCLUDES})