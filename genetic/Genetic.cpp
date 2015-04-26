#include <iostream>
#include <cmath>
#include <memory>
#include <algorithm>
#include "Genetic.h"


Genetic::Genetic(int populationSize)
    : populationSize(populationSize),
      nnSizes({Field::fieldWidth * Field::fieldHeight, 10, 10, 10, (int) Button::_COUNT}) {
    chromosomeSize = 0;
    for (int i = 1; i < nnSizes.size(); ++i) {
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
}

Genetic::Button Genetic::activate(const Field& field) {
    GeneticField geneticField = createGeneticField(field);
    printGeneticField(geneticField);

    // chromosome = [ l1_11 l1_21 .. l1_j1 l1_b1 ... l1_1s l1_2s .. l1_js l1_bs .....  ]
    Chromosome chromosome(chromosomeSize);

    typedef std::vector<double> vec;
    typedef std::shared_ptr<vec> vec_ptr;

    vec input = geneticFieldToInput(geneticField);
    vec_ptr layer_p = nullptr;
    vec_ptr prevLayer_p = std::make_shared<vec>(input);

    int c = 0;
    for (int layerId = 1; layerId < nnSizes.size(); ++layerId) {
        int layerSize = nnSizes[layerId];
        int prevLayerSize = nnSizes[layerId - 1];

        layer_p = std::make_shared<vec>(layerSize);
        std::vector<double>& layer = *layer_p;
        std::vector<double>& prevLayer = *prevLayer_p;
        for (int i = 0; i < layerSize; ++i) {
            for (int j = 0; j < prevLayerSize; ++j) {
                layer[i] += chromosome.genome[c] * prevLayer[j];
                c += 1;
            }
            layer[i] += chromosome.genome[c++];  // bias
            layer[i] = std::atan(layer[i]);  // activate neuron
        }

        prevLayer_p = layer_p;

    }

    auto result = std::max_element(layer_p->begin(), layer_p->end());
    int buttonId = std::distance(layer_p->begin(), result);

    std::cout << "Button: " << buttonId << std::endl;

    return static_cast<Button>(buttonId);
}

void Genetic::printGeneticField(GeneticField &geneticField) {
    std::cout << "=================================" << std::endl;
    for (int i = 0; i < geneticField.size(); ++i) {
        for (int j = 0; j < geneticField[i].size(); ++j) {
            std::cout << geneticField[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Genetic::step(int score) {

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
    //    const Figure& figure = field.getFigure();
    //    for (int i = 0; i < figureSize; ++i) {
    //        for (int j = 0; j < figureSize; ++j) {
    //            geneticField[figure.dx + i][figure.dy + j] = figure.at(i, j) ? 2 : 0;
    //        }
    //    }

    return geneticField;
}

std::vector<double> Genetic::geneticFieldToInput(GeneticField field) {
    std::vector<double> input(field.size() * field[0].size());
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[i].size(); ++j) {
            input[i * field[i].size() + j] = static_cast<double>(field[i][j]);
        }
    }
    return input;
}