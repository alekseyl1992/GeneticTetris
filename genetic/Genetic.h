#ifndef TETRIS_GENETIC_H
#define TETRIS_GENETIC_H
#include <vector>
#include "Field.h"
#include "Chromosome.h"

using GeneticRow = std::vector<int>;
using GeneticField = std::vector<GeneticRow>;
using Pool = std::vector<Chromosome>;

using namespace Tetris;
class Genetic {
public:
    enum class Button {
        LEFT, RIGHT, ROTATE, NONE, _COUNT
    };

    Genetic(int populationSize = 20, double mutationProbability = 1./50.);

    Button activate(const Field& field);
    void init();
    void step(int score);

    void newGeneration();

    GeneticField createGeneticField(Field const &field);
    void printGeneticField(GeneticField &geneticField);
    std::vector<double> geneticFieldToInput(const GeneticField& field);

private:
    int populationSize;
    std::vector<int> nnSizes;
    size_t chromosomeSize;
    double mutationProbability;
    Pool pool;
    int currentChromosomeId;
};

#endif //TETRIS_GENETIC_H
