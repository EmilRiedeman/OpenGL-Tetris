cmake_minimum_required(VERSION 3.16)

set(SOURCE main.cpp)

add_subdirectory(graphics)
add_subdirectory(tetris)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE tetris)
