cmake_minimum_required(VERSION 3.19)
project(lm962 C)

set(CMAKE_C_STANDARD 99)

set(PROGRAM_SRCS
        sources/reels/reels.c
        sources/gameboard/gameboard.c
        sources/stats/stats.c
        sources/engine/engine.c
        sources/main.c
        )

add_executable(lm962 ${PROGRAM_SRCS})