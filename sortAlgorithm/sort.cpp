//
// Created by claim on 16-12-22.
//

#include "generator.h"
#include <algorithm>

using std::make_heap;
using std::pop_heap;

template<typename D>
void insertionSort (vector<D> &target, int step = 1, int origin = 0) {
    //Stable
    for (int i = origin + step; i < target.size(); i += step) {
        auto temp = target[i];
        int j = i;
        for (; j >= origin + step && target[j - step] > temp; j -= step) {
            target[j] = target[j - step];
        }
        target[j] = temp;
    }
}

template<typename D>
void binaryInsertionSort (vector<D> &target) {
    //Stable
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
        auto temp = target[i];
        for (int j = i; j > head; --j) {
            target[j] = target[j - 1];
        }
        target[head] = temp;

    }
}


template<typename D>
void shellSort (vector<D> &target) {
    //Unstable
    int step = (int) ((target.size() + 1) / 2);
    while (step > 0) {
        insertionSort(target, step, 0);
        step /= 2;
    }
}

template<typename D>
void bubbleSort (vector<D> &target) {
    //Stable
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

template<typename D>
void heapSort (vector<D> &target) {
    //Unstable
    make_heap(target.begin(), target.end());
    for (unsigned long i = target.size(); i > 0; --i) {
        pop_heap(target.begin(), target.begin() + i);
    }
}

template<typename D>
void selectSort (vector<D> &target) {
    //Unstable
    for (int i = 0; i < target.size() - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < target.size(); ++j) {
            if (target[j] < target[min])
                min = j;
        }
        if (min != i) {
            target[min] ^= target[i];
            target[i] ^= target[min];
            target[min] ^= target[i];
        }
    }
}

template<typename D>
void mergeSort (typename vector<D>::iterator begin, typename vector<D>::iterator end, vector<D> &helper) {
    //Stable
    if (end - begin > 1) {
        auto divider = begin + (end - begin + 1) / 2;
        mergeSort(begin, divider, helper);
        mergeSort(divider, end, helper);
        helper.clear();
        auto front = begin, back = divider;
        while (front < divider && back < end) {
            if (*back >= *front) {
                helper.push_back(*front);
                front++;
            } else {
                helper.push_back(*back);
                back++;
            }
        }
        while (front < divider) {
            helper.push_back(*front);
            front++;
        }
        while (back < end) {
            helper.push_back(*back);
            back++;
        }
        for (int i = 0; i < end - begin; ++i) {
            *(begin + i) = helper[i];
        }
    }
}

template<typename D>
void mergeSort (vector<D> &target) {
    //Stable
    vector<D> helper;
    mergeSort(target.begin(), target.end(), helper);
}

template<typename D>
void quickSort (typename vector<D>::iterator begin, typename vector<D>::iterator end) {
    //Unstable
    if (end - begin > 1) {
        int divider = rand() % (end - begin);
        if (begin + divider != end - 1) {
            *(begin + divider) ^= *(end - 1);
            *(end - 1) ^= *(begin + divider);
            *(begin + divider) ^= *(end - 1);
        }
        divider = 0;
        int greaterDivider = 0, lessDivider = 0;
        while (begin + greaterDivider < end - 1) {
            if (*(begin + greaterDivider) < *(end - 1)) {
                //swap m g
                if (divider != greaterDivider) {
                    *(begin + greaterDivider) ^= *(begin + divider);
                    *(begin + divider) ^= *(begin + greaterDivider);
                    *(begin + greaterDivider) ^= *(begin + divider);
                }
                //swap l m
                if (divider != lessDivider) {
                    *(begin + lessDivider) ^= *(begin + divider);
                    *(begin + divider) ^= *(begin + lessDivider);
                    *(begin + lessDivider) ^= *(begin + divider);
                }
                lessDivider++;
                divider++;
                greaterDivider++;
            } else if (*(begin + greaterDivider) == *(end - 1)) {
                //swap m g
                if (divider != greaterDivider) {
                    *(begin + greaterDivider) ^= *(begin + divider);
                    *(begin + divider) ^= *(begin + greaterDivider);
                    *(begin + greaterDivider) ^= *(begin + divider);
                }
                divider++;
                greaterDivider++;
            } else {
                greaterDivider++;
            }
        }
        if (begin + greaterDivider != end - 1) {
            *(begin + greaterDivider) ^= *(begin + divider);
            *(begin + divider) ^= *(begin + greaterDivider);
            *(begin + greaterDivider) ^= *(begin + divider);
        }
        greaterDivider++;
        quickSort<D>(begin, begin + lessDivider);
        quickSort<D>(begin + divider, begin + greaterDivider);
    }
}

template<typename D>
void quickSort (vector<D> &target) {
    //Unstable
    if (target.size() < 10) {
        insertionSort(target);
        return;
    }
    srand((unsigned int) time(0));
    quickSort<D>(target.begin(), target.end());
}

void radixSort (vector<unsigned> &target) {
    //Stable
    int digit = 1;
    vector<vector<unsigned>> bucket(10);
    while (1) {
        for (int i = 0; i < target.size(); ++i) {
            bucket[target[i] / (int) pow(10, digit) % 10].push_back(target[i]);
        }
        target.clear();
        if (bucket[0].size() == 10) {
            target.insert(target.end(), bucket[0].begin(), bucket[0].end());
            break;
        }
        for (int j = 0; j < 10; ++j) {
            target.insert(target.end(), bucket[j].begin(), bucket[j].end());
            bucket[j].clear();
        }
        digit++;
    }
}

int main () {
    auto container_1 = randomSequenceGenerator<int>(10);
    auto container_2 = randomSequenceGenerator<int>(10);
    auto container_3 = randomSequenceGenerator<int>(10);
    auto container_4 = randomSequenceGenerator<int>(10);
    auto container_5 = randomSequenceGenerator<int>(10);
    auto container_6 = randomSequenceGenerator<int>(10);
    auto container_7 = randomSequenceGenerator<int>(10);
    auto container_8 = randomSequenceGenerator<int>(10);
    auto container_9 = randomSequenceGenerator<unsigned>(10);
    insertionSort(container_1);
    binaryInsertionSort(container_2);
    shellSort(container_3);
    bubbleSort(container_4);
    heapSort(container_5);
    selectSort(container_6);
    mergeSort(container_7);
    quickSort(container_8);
    radixSort(container_9);
    return 0;
}