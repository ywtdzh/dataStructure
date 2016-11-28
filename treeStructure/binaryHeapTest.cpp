//
// Created by claim on 16-11-27.
//

#include "binaryHeap.h"
#include <assert.h>

int main () {
    binaryMaxHeap<int> heap;
    heap.addData(9);
    heap.addData(3);
    assert(heap.size() == 2);
    heap.addData(12);
    heap.addData(0);
    assert(heap.getMax() == 12);
    heap.removeDataByIndex(1);
    assert(heap.getMax() == 9);
    assert(heap.exist(9));
    return 0;
}