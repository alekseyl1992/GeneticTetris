#include "WorkerThread.h"

WorkerThread::WorkerThread(int populationSize, QObject *parent) :
    QThread(parent), populationSize(populationSize)
{
}

void WorkerThread::run()
{
    Genetic genetic(populationSize, 1./.100);
    genetic.init();

    loop = true;
    while(loop) {
        GameResult result = gameRun(genetic);
        emit statsChanged(genetic.getCurrentChromosomeId(),
                          result.scores,
                          result.stepsCount,
                          result.fitness);

        genetic.step(result.scores, result.fitness);
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
    auto fitness = genetic.evalFitness(score, gameStepsCount, game.getField());

    return {score, gameStepsCount, fitness};
}
