#-------------------------------------------------
#
# Project created by QtCreator 2015-04-27T22:14:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
	MainWindow.cpp \
    Field.cpp \
    Figure.cpp \
    genetic/Chromosome.cpp \
    genetic/Genetic.cpp \
    genetic/GeneticGame.cpp \
    genetic/util.cpp \
    WorkerThread.cpp

HEADERS  += MainWindow.h \
    Field.h \
    Figure.h \
    IGame.h \
    genetic/Chromosome.h \
    genetic/Genetic.h \
    genetic/GeneticGame.h \
    genetic/util.h \
    main/GeneticGame.h \
    WorkerThread.h

FORMS    += MainWindow.ui

OTHER_FILES += \
    .gitignore
