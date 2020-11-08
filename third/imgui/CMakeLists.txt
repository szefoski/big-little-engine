cmake_minimum_required(VERSION 3.0)
project(ImGui)

include(FetchContent)

FetchContent_Declare(
  imgui_git
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG        b7530e5d04fcd9d5859c089244f562be82b4c531
  GIT_PROGRESS   TRUE
  USES_TERMINAL_DOWNLOAD TRUE
)

FetchContent_GetProperties(imgui_git)
if(NOT imgui_git_POPULATED)
  FetchContent_Populate(imgui_git)
endif()

add_library(imgui 
    ${imgui_git_SOURCE_DIR}/imgui.cpp
    ${imgui_git_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_git_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_git_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_git_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

target_include_directories(imgui PUBLIC ${imgui_git_SOURCE_DIR} PRIVATE ${GLAD_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})