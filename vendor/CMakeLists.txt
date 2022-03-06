cmake_minimum_required(VERSION 3.16)

add_subdirectory(glfw)
add_subdirectory(glew)

set(LIBS glfw libglew_static PARENT_SCOPE)