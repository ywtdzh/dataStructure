//
// Created by claim on 16-9-25.
//

#include "doubleWayCycleChain.h"

int main() {
    doubleWayCycleChain chain(1);
    chain.addNode(5);
    chain.addNode(3);
    chain.addNode(5);
    chain.printChain();
    chain.deleteOneByValue(5);
    chain.printChain();
    chain.deleteOneByValue(5);
    chain.deleteOneByValue(3);
    chain.deleteOneByValue(1);
    chain.deleteOneByValue(1);
    chain.printChain();
    chain.addNode(6);
    chain.deleteOneByValue(1);
    chain.printChain();
}