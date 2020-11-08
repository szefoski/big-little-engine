cmake_minimum_required(VERSION 3.0)
project(Glad)

add_library(glad include/glad/glad.h src/glad.c)
set( GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE STRING "" )
target_include_directories(glad PUBLIC include/)