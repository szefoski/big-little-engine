cmake_minimum_required( VERSION 3.1 )
project( lbe_example_project )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

set( FETCHCONTENT_QUIET OFF CACHE BOOL "" )

message("Chosen ${CMAKE_GENERATOR} generator")

string(REPLACE " " "_" FETCHCONTENT_DIR_GENERATOR_NAME ${CMAKE_GENERATOR})
set (FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/third-download-cache/${FETCHCONTENT_DIR_GENERATOR_NAME}" CACHE STRING "")

# spdlog
add_subdirectory( third/spdlog )

# OpenGL
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

# GLAD
add_subdirectory( third/glad/ )

# stb_image
add_subdirectory( third/stb/ )

# GLM
add_subdirectory( third/glm )

# GLFW
add_subdirectory( third/glfw )

# imgui //must be after GLFW and GLAD
add_subdirectory( third/imgui )


## LBE libary
set( lbe_src
    src/ogl_object_3d.cc
    src/ogl_program_shader.cc
    src/ogl_shape.cc
    src/ogl_texture.cc
    src/ogl_texture_mvp.cc
    src/ogl_textures_bank.cc
    src/utils.cc
    )

add_library(lbe ${lbe_src})
target_include_directories(lbe PUBLIC include/)

target_link_libraries( lbe
    PUBLIC
    ${OPENGL_LIBRARIES}
    glad_build
    glfw
    glm
    stb
    imgui
    spdlog
    )


## App Example
set( app_src
    examples/basics/main.cc
)

add_executable( lbe_example
    ${app_src}
    )

target_link_libraries( lbe_example
    PRIVATE
    lbe
    )

install( TARGETS lbe_example DESTINATION bin )