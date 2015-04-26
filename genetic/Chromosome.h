#ifndef TETRIS_CHROMOSOME_H
#define TETRIS_CHROMOSOME_H

#include <vector>

using Genome = std::vector<double>;
struct Chromosome {
    Genome genome;
    double fitness;

    Chromosome(int size);
    static Chromosome createRandom(int size);
};


#endif //TETRIS_CHROMOSOME_H
