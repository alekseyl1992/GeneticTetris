#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include "genetic/GeneticGame.h"

struct GameResult {
    int scores = 0;
    int stepsCount = 0;

    GameResult(int scores, int stepsCount)
        : scores(scores), stepsCount(stepsCount)
    { }
};

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent, int populationSize);
    virtual void stop();

private:
    GameResult gameRun(Genetic& genetic);
    bool loop;
    int populationSize;

protected:
    virtual void run();

signals:
    void fieldChanged(const Field& field);
    void statsChanged(int chromosomeId, int score, int gameStepsCount);

public slots:

};

#endif // WORKERTHREAD_H
