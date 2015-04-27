cmake_minimum_required(VERSION 3.1)
project(Tetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(.)

set(SOURCE_FILES
    lib/arduino_utils.h
    lib/deps.h
    Field.cpp
    Field.h
    Figure.cpp
    Figure.h
    IGame.h

    )

add_executable(TetrisConsole ${SOURCE_FILES} console/ConsoleGame.cpp
                                             console/ConsoleGame.h
                                             main/ConsoleMain.cpp
                                             )

add_executable(TetrisGenetic ${SOURCE_FILES} genetic/Chromosome.cpp
                                             genetic/Chromosome.h
                                             genetic/GeneticGame.cpp
                                             genetic/GeneticGame.h
                                             genetic/Genetic.cpp
                                             genetic/Genetic.h
                                             main/GeneticMain.cpp
                                             genetic/util.h genetic/util.cpp)
