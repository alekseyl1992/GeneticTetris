#ifndef TETRIS_UTIL_H
#define TETRIS_UTIL_H

#include <cstdlib>

double rand01() {
    return static_cast<double>(std::rand()) / RAND_MAX;
}

int randAB(int a, int b) {
    assert(a <= b);
    return static_cast<int>(rand01() * (b - a) + a);
}

#endif //TETRIS_UTIL_H
