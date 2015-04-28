#include "util.h"
#include <random>

double rand01() {
    static std::default_random_engine generator;

    std::uniform_real_distribution<double> distribution(0, 1);
    return distribution(generator);
}

int randAB(int a, int b) {
    static std::default_random_engine generator;

    std::uniform_int_distribution<int> distribution(a, b - 1);
    return distribution(generator);
}
