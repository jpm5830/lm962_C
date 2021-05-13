cmake_minimum_required(VERSION 3.19)
project(lm962 C)

set(CMAKE_C_STANDARD 99)

add_executable(lm962 main.c reels.c reels.h gameboard.c gameboard.h stats.c stats.h engine.c engine.h)
