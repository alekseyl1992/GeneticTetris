#include "util.h"
#include <random>
#include <iostream>

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

int randABexp(int a, int b) {
    static std::default_random_engine generator;

    std::exponential_distribution<double> distribution(1);
    int id = distribution(generator) * (b - a) + a;
    std::cout << id << std::endl;
}
