//
// Created by claim on 16-12-22.
//

#include "generator.h"

template<typename D>
void insertionSort (vector<D> &target, int step = 1, int origin = 0) {
    int final = target.size() - 1 - (target.size() - 1) % step;
    for (int i = origin + step; i < target.size(); i += step) {
        for (int j = i; j > origin + step - 1; j -= step) {
            if (target[j] < target[j - step]) {
                target[j] ^= target[j - step];
                target[j - step] ^= target[j];
                target[j] ^= target[j - step];
            } else {
                break;
            }
        }
    }
}

template<typename D>
void binaryInsertionSort (vector<D> &target) {
    int head, tail, index;
    for (int i = 1; i < target.size(); ++i) {
        head = 0;
        tail = i - 1;
        while (head <= tail) {
            index = (head + tail) / 2;
            if (target[i] < target[index]) {
                tail = index - 1;
            } else {
                head = index + 1;
            }
        }
        for (int j = i; j > head; --j) {
            target[j] ^= target[j - 1];
            target[j - 1] ^= target[j];
            target[j] ^= target[j - 1];
        }

    }
}


template<typename D>
void shellSort (vector<D> &target) {
    int step = (int) ((target.size() + 1) / 2);
    while (step > 0) {
        insertionSort(target, step, 0);
        step /= 2;
    }
}

template<typename D>
void bubbleSort (vector<D> &target) {
    bool changed;
    for (int i = 0; i < target.size() - 1; ++i) {
        changed = false;
        for (int j = 0; j < target.size() - i - 1; ++j) {
            if (target[j] > target[j + 1]) {
                target[j] ^= target[j + 1];
                target[j + 1] ^= target[j];
                target[j] ^= target[j + 1];
                changed = true;
            }
        }
        if (!changed)
            break;
    }
}

int main () {
    auto container_1 = randomSequenceGenerator<int>(10);
    insertionSort(container_1);
    auto container_2 = randomSequenceGenerator<int>(10);
    binaryInsertionSort(container_2);
    auto container_3 = randomSequenceGenerator<int>(10);
    shellSort(container_3);
    auto container_4 = randomSequenceGenerator<int>(10);
    bubbleSort(container_4);
    return 0;
}