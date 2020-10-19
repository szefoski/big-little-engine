cmake_minimum_required( VERSION 3.1 )
project( lbe_example_project )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# OpenGL
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

# GLAD
add_subdirectory(third/glad/)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory( third/glfw )
#include_directories(third/glfw/include)

# GLM
add_subdirectory( third/glm )

add_executable(lbe_example
    main.cpp
    program_shader.cpp
    shape.cpp
    stb_image.cpp
    texture.cpp
    textureMVP.cpp
    texturesBank.cpp
    utils.cpp
    )

target_link_libraries(lbe_example PRIVATE ${OPENGL_LIBRARIES} glad glfw glm)

install(TARGETS lbe_example DESTINATION bin)