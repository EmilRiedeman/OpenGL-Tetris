cmake_minimum_required(VERSION 3.16)
project(OpenGLTetris)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(glfw/)
add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)