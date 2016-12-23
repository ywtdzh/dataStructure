//
// Created by claim on 16-12-22.
//

#ifndef DATASTRUCTURE_GENERATOR_H
#define DATASTRUCTURE_GENERATOR_H

#include <vector>
#include <ctime>
#include <cstdlib>

using std::vector;

template<typename D>
vector<D> randomSequenceGenerator (int size = 10) {
    srand(time(0));
    vector<D> temp;
    for (int i = 0; i < size; ++i) {
        temp.push_back(rand() % 1000);
    }
    return temp;
}

#endif //DATASTRUCTURE_GENERATOR_H
