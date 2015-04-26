#include <assert.h>
#include "Chromosome.h"
#include "util.h"

Chromosome::Chromosome(size_t size)
    : genome(size), fitness(0) {

}

Chromosome Chromosome::createRandom(size_t size) {
    Chromosome chromosome(size);

    for (int i = 0; i < size; ++i) {
        auto rand = rand01();
        chromosome.genome[i] = rand * 2 - 1;
    }

    return chromosome;
}

void Chromosome::mutate(double mutationProbability) {
    for (int i = 0; i < genome.size(); ++i) {
        auto rand = rand01();
        if (rand < mutationProbability) {
            genome[i] = rand * 2 - 1;
        }
    }
}

Chromosome Chromosome::crossover(const Chromosome& c1, const Chromosome& c2) {
    assert(c1.genome.size() == c2.genome.size());
    Chromosome c(c1.genome.size());

    double prob = 1. / (c.genome.size() / 4.);
    bool doPick = true;
    for (int i = 0; i < c.genome.size(); ++i) {
        if (rand01() < prob) {
            doPick = !doPick;
        }
        c.genome[i] = doPick ? c1.genome[i] : c2.genome[i];
    }
    return c;
}


