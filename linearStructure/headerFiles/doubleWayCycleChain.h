//
// Created by claim on 16-9-25.
//

#ifndef DATASTRUCTURE_DOUBLEWAYCYCLECHAIN_H
#define DATASTRUCTURE_DOUBLEWAYCYCLECHAIN_H

#include "data.h"

class doubleWayCycleChain {
    struct chain {
        data content;
        chain *next, *prev;
    };
    typedef struct chain chain;
    typedef chain node;
    chain *list;
public:
    doubleWayCycleChain(data source);

    void addNode(data source);

    void printChain();

    void deleteOneByValue(data value);
};


#endif //DATASTRUCTURE_DOUBLEWAYCYCLECHAIN_H
