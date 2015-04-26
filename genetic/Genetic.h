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
private:
    int populationSize;
    std::vector<int> nnSizes;
    int chromosomeSize;
    Pool pool;

public:
    Genetic(int populationSize);

    enum class Button {
        LEFT, RIGHT, ROTATE, NONE, _COUNT
    };

    Button activate(const Field& field);

    void init();

    void step(int score);

    GeneticField createGeneticField(Field const &field);

    void printGeneticField(GeneticField &geneticField);

    std::vector<double> geneticFieldToInput(GeneticField field);
};

#endif //TETRIS_GENETIC_H
