#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include "genetic/GeneticGame.h"

struct GameResult {
    int scores = 0;
    int stepsCount = 0;
    double fitness = 0.0;

    GameResult(int scores, int stepsCount, double fitness)
        : scores(scores), stepsCount(stepsCount), fitness(fitness)
    { }
};

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(int populationSize, QObject *parent=nullptr);
    virtual void stop();

private:
    GameResult gameRun(Genetic& genetic);
    bool loop;
    int populationSize;

protected:
    virtual void run();

signals:
    void fieldChanged(const Field& field);
    void statsChanged(const Pool& pool);

public slots:

};

#endif // WORKERTHREAD_H
