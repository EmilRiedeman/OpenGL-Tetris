cmake_minimum_required(VERSION 3.16)

add_library(tetris Game.hpp Game.cpp Tetromino.cpp Tetromino.hpp Vec2.hpp Color.hpp)
#target_link_libraries(tetris PRIVATE ${LIBS})