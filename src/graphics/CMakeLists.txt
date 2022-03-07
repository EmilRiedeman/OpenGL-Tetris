cmake_minimum_required(VERSION 3.16)

add_library(graphics Display.hpp Display.cpp)
target_link_libraries(graphics PRIVATE ${LIBS})