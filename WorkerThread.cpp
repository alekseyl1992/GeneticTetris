#include "WorkerThread.h"

WorkerThread::WorkerThread(QObject *parent, int populationSize) :
    QThread(parent), populationSize(populationSize)
{
}

void WorkerThread::run()
{
    Genetic genetic(populationSize, 1./.10);
    genetic.init();

    loop = true;
    while(loop) {
        GameResult result = gameRun(genetic);
        genetic.step(result.scores, result.stepsCount);

        emit statsChanged(genetic.getCurrentChromosomeId(),
                          result.scores,
                          result.stepsCount);
    }
}

void WorkerThread::stop()
{
    loop = false;
}

GameResult WorkerThread::gameRun(Genetic& genetic) {
    Tetris::GeneticGame game(genetic);
    QObject::connect(&game,
                     &Tetris::GeneticGame::fieldChanged,
                     [&] (const Field& field) {
        emit fieldChanged(field);
    });

    auto score = game.begin();
    auto gameStepsCount = game.getStepsCount();

    return {score, gameStepsCount};
}
