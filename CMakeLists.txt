cmake_minimum_required(VERSION 3.1)
project(Tetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

include_directories(.)

set(SOURCE_FILES
    lib/arduino_utils.h
    Field.cpp
    Field.h
    Figure.cpp
    Figure.h
    IGame.h
    lib/kbhit.h
    )

add_executable(TetrisConsole ${SOURCE_FILES} main/ConsoleMain.cpp console/ConsoleGame.cpp
    console/ConsoleGame.h)
add_executable(TetrisGenetic ${SOURCE_FILES} main/GeneticMain.cpp genetic/Chromosome.cpp genetic/Chromosome.h genetic/GeneticGame.cpp
    genetic/GeneticGame.h
    genetic/Genetic.cpp
    genetic/Genetic.h)
