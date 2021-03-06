#include <iostream>
#include <cmath>
#include <memory>
#include <algorithm>
#include "Genetic.h"
#include "util.h"


Genetic::Genetic(int populationSize, double mutationProbability)
    : populationSize(populationSize),
      nnSizes({Field::fieldWidth * Field::fieldHeight, 20, 10, 10, 10, (int) Button::_COUNT}),
      chromosomeSize(0),
      mutationProbability(mutationProbability),
      currentChromosomeId(-1) {

    for (size_t i = 1; i < nnSizes.size(); ++i) {
        auto prevLayerSize = nnSizes[i - 1];
        auto layerSize = nnSizes[i];
        chromosomeSize += (prevLayerSize + 1) * layerSize;
    }
}

void Genetic::init() {
    for (int i = 0; i < populationSize; ++i) {
        Chromosome chromosome = Chromosome::createRandom(chromosomeSize);
        pool.push_back(chromosome);
    }
    currentChromosomeId = 0;
}

Genetic::Button Genetic::activate(const Field& field) {
    GeneticField geneticField = createGeneticField(field);
//    printGeneticField(geneticField);

    // chromosome = [ l1_11 l1_21 .. l1_j1 l1_b1 ... l1_1s l1_2s .. l1_js l1_bs .....  ]

    typedef std::vector<double> vec;
    typedef std::shared_ptr<vec> vec_ptr;

    vec input = geneticFieldToInput(geneticField);
    vec_ptr layer_p = nullptr;
    vec_ptr prevLayer_p = std::make_shared<vec>(input);

    int c = 0;
    for (size_t layerId = 1; layerId < nnSizes.size(); ++layerId) {
        int layerSize = nnSizes[layerId];
        int prevLayerSize = nnSizes[layerId - 1];

        layer_p = std::make_shared<vec>(layerSize);
        vec& layer = *layer_p;
        vec& prevLayer = *prevLayer_p;
        for (int i = 0; i < layerSize; ++i) {
            for (int j = 0; j < prevLayerSize; ++j) {
                layer[i] += pool[currentChromosomeId].genome[c] * prevLayer[j];
                c += 1;
            }
            layer[i] += pool[currentChromosomeId].genome[c++];  // bias
            layer[i] = std::atan(layer[i]);  // activate neuron
        }

        prevLayer_p = layer_p;

    }

    auto result = std::max_element(layer_p->begin(), layer_p->end());
    int buttonId = std::distance(layer_p->begin(), result);

    return static_cast<Button>(buttonId);
}

void Genetic::printGeneticField(GeneticField &geneticField) {
    std::cout << "=================================" << std::endl;
    for (size_t i = 0; i < geneticField.size(); ++i) {
        for (size_t j = 0; j < geneticField[i].size(); ++j) {
            std::cout << geneticField[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double Genetic::evalFitness(int score, int gameStepsCount, const Field &field) {
    auto geneticField = createGeneticField(field);
    double nonZeroAvg = 0.0;
    assert(Field::fieldHeight == geneticField.size());
    for (size_t i = 0; i < Field::fieldHeight; ++i) {
        double avg = 0.0;
        assert(Field::fieldWidth == geneticField[i].size());
        for (size_t j = 0; j < Field::fieldWidth; ++j) {
            if (geneticField.at(i).at(j) != 0) {
                ++avg;
            }
        }
        nonZeroAvg += avg / Field::fieldWidth;
    }
    nonZeroAvg /= Field::fieldHeight;
    constexpr double FACTOR = 100.0d;
//    return double(score) * 10 + double(gameStepsCount) / FACTOR;
    return 0.7 * double(score) + 0.3 * nonZeroAvg;
}

void Genetic::step(int score, double fitness) {
    pool[currentChromosomeId].fitness = fitness;
    pool[currentChromosomeId].score = score;

//    if (score >= maxScores && score != 0) {
//        maxScores = score;

//        // clone the champion
//        int replacePos = pool.size() - 1;
//        constexpr int clonesCount = 3;

//        for (int i = 0; i < clonesCount; ++i) {
//            auto champion = pool[currentChromosomeId];
//            clone(champion, replacePos--);
//        }
//    }

    if (++currentChromosomeId >= pool.size()) {  // end of generation
        newGeneration();
        currentChromosomeId = 0;
    }
}

void Genetic::clone(const Chromosome& chromosome, int insertPos) {
    Chromosome clone = chromosome;
    clone.mutate(1./100.);

    pool[insertPos] = clone;
}

GeneticField Genetic::createGeneticField(const Field &field) {
    // project field
    GeneticField geneticField(Field::fieldHeight);
    for (int i = 0; i < Field::fieldHeight; ++i) {
        GeneticRow geneticRow(Field::fieldWidth);
        for (int j = 0; j < Field::fieldWidth; ++j) {
            bool bValue = field.at(j, i);
            geneticRow[j] = bValue;
        }

        geneticField[i] = geneticRow;
    }

    // project matrix figure
    const Figure& figure = field.getFigure();
    for (int i = 0; i < figureSize; ++i) {
        for (int j = 0; j < figureSize; ++j) {
            if (figure.at(i, j)
                    && figure.dx + i >= 0
                    && figure.dy + j >= 0
                    && figure.dx + i < Field::fieldWidth
                    && figure.dy + j < Field::fieldHeight) {
                geneticField[figure.dy + j][figure.dx + i] = 2;
            }
        }
    }

    //printGeneticField(geneticField);

    return geneticField;
}

std::vector<double> Genetic::geneticFieldToInput(const GeneticField& field) {
    std::vector<double> input(field.size() * field[0].size());
    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[i].size(); ++j) {
            input[i * field[i].size() + j] = static_cast<double>(field[i][j]);
        }
    }
    return input;
}
int Genetic::getCurrentChromosomeId() const
{
    return currentChromosomeId;
}

const Pool &Genetic::getPopulation() const
{
    return pool;
}

void Genetic::newGeneration() {
    std::sort(pool.begin(), pool.end(), [](auto& lhs, auto& rhs) {
        return lhs.fitness > rhs.fitness;
    });
    
    size_t middle = pool.size() / 7;
    for (size_t i = middle; i < pool.size(); ++i) {
        auto& c1 = pool[randABexp(0, middle)];
        auto& c2 = pool[randABexp(0, middle)];

        pool[i] = Chromosome::crossover(c1, c2);
        pool[i].mutate(mutationProbability);
    }
}

void Genetic::newGeneration2() {
    std::sort(pool.begin(), pool.end(), [](auto& lhs, auto& rhs) {
        return lhs.fitness > rhs.fitness;
    });

    size_t middle = pool.size() / 2;
    size_t j = 0;
    for (size_t i = middle; i < pool.size(); ++i) {
        auto& c1 = pool[j];
        auto c1Clone = c1.clone();
        pool[i] = c1Clone.mutateShuffle(0.3);
        if (rand01() < 0.08) {
            pool[j].mutateShuffle(0.3);
        }
        ++j;
    }
}
