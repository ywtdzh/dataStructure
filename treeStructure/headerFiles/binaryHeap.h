//
// Created by claim on 16-11-27.
//

#ifndef DATASTRUCTURE_BINARYHEAP_H
#define DATASTRUCTURE_BINARYHEAP_H

#include <vector>
#include <exception>

using namespace std;

template<typename D>
class binaryMaxHeap {
    vector<D> heap;
public:
    binaryMaxHeap ();

    unsigned addData (const D &data);

    unsigned removeDataByValue (const D &data);

    unsigned removeDataByIndex (const unsigned index);

    inline D getMax ();

    inline unsigned size ();

    bool exist (const D &data);
};

template<typename D>
binaryMaxHeap<D>::binaryMaxHeap () {}

template<typename D>
unsigned binaryMaxHeap<D>::removeDataByValue (const D &data) {
    if (data > getMax())
        return 0;
    for (int i = 0; i < heap.size(); ++i) {
        if (heap[i] == data) {
            removeDataByIndex(i + 1);
            return 1;
        }
    }
    return 0;
}

template<typename D>
unsigned binaryMaxHeap<D>::removeDataByIndex (const unsigned index) {
    int current = index;
    if (index > heap.size() || !index > 0)
        return 0;
    heap[current - 1] = heap[heap.size() - 1];
    heap.erase(heap.end() - 1);
    while (current * 2 < heap.size()) {
        if (heap[current * 2] < heap[current * 2 - 1] && heap[current * 2 - 1] > heap[current - 1]) {
            heap[current - 1] ^= heap[current * 2 - 1];
            heap[current * 2 - 1] ^= heap[current - 1];
            heap[current - 1] ^= heap[current * 2 - 1];
            current = current * 2 - 1;
        } else if (heap[current * 2] >= heap[current * 2 - 1] && heap[current * 2] > heap[current - 1]) {
            heap[current - 1] ^= heap[current * 2];
            heap[current * 2] ^= heap[current - 1];
            heap[current - 1] ^= heap[current * 2];
            current = current * 2;
        } else {
            break;
        }
    }
    if (heap[current * 2 - 1] < heap.size() && heap[current * 2 - 1] > heap[current - 1]) {
        heap[current - 1] ^= heap[current * 2 - 1];
        heap[current * 2 - 1] ^= heap[current - 1];
        heap[current - 1] ^= heap[current * 2 - 1];
        current = current * 2 - 1;
    }
    return 1;
}

template<typename D>
unsigned binaryMaxHeap<D>::addData (const D &data) {
    heap.push_back(data);
    unsigned current = heap.size();
    while (current / 2 > 0) {
        if (heap[current - 1] > heap[current / 2 - 1]) {
            heap[current - 1] ^= heap[current / 2 - 1];
            heap[current / 2 - 1] ^= heap[current - 1];
            heap[current - 1] ^= heap[current / 2 - 1];
            current /= 2;
        } else {
            return current;
        }
    }
    return current;

}

template<typename D>
inline D binaryMaxHeap<D>::getMax () {
    if (!heap.empty())
        return heap[0];
    else
        throw exception();
}

template<typename D>
inline unsigned binaryMaxHeap<D>::size () {
    return heap.size();
}

template<typename D>
bool binaryMaxHeap<D>::exist (const D &data) {
    if (data > getMax())
        return false;
    for (int i = 0; i < heap.size(); ++i) {
        if (heap[i] == data) {
            return true;
        }
    }
    return false;
}

#endif //DATASTRUCTURE_BINARYHEAP_H
