#include "Chromosome.h"
#include <cstdlib>

Chromosome::Chromosome(int size)
    : genome((unsigned int) size), fitness(0) {

}

Chromosome Chromosome::createRandom(int size) {
    Chromosome chromosome(size);

    for (int i = 0; i < size; ++i) {
        auto rand = static_cast<double>(std::rand()) / RAND_MAX;
        chromosome.genome[i] = rand * 2 - 1;
    }

    return chromosome;
}
