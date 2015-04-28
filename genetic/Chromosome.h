#ifndef TETRIS_CHROMOSOME_H
#define TETRIS_CHROMOSOME_H

#include <vector>
#include <cstdlib>

using Genome = std::vector<double>;
struct Chromosome {
    Genome genome;
    int score;
    double fitness;

    Chromosome(size_t size);
    Chromosome clone();
    Chromosome& mutate(double mutationProbability);
    Chromosome& mutateShuffle(double shufflePercent);

    static Chromosome createRandom(size_t size);
    static Chromosome crossover(const Chromosome& c1, const Chromosome& c2);
};


#endif //TETRIS_CHROMOSOME_H
