cmake_minimum_required(VERSION 3.20)
project(2048 C)

set(CMAKE_C_STANDARD 11)

include_directories(include/)

add_executable(${PROJECT_NAME} main.c include/ttfe.h src/board.c)