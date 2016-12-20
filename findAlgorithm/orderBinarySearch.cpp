//
// Created by claim on 16-12-19.
//

#include <vector>
#include <assert.h>

using std::vector;

template<typename D>
typename vector<D>::iterator orderSearch (vector<D> &where, const D &target) {
    for (auto iter = where.begin(); iter < where.end(); iter++) {
        if (*iter == target)
            return iter;
    }
    return where.end();
}

template<typename D>
typename vector<D>::iterator minBinarySearch (vector<D> &where, const D &target) { //从小到大排序
    auto begin = where.begin();
    int index = where.size() / 2, head = 0, tail = where.size();
    while (head > tail) {
        if (*(begin + index) == target)
            return begin + index;
        else if (*(begin + index) < target) {
            head = index + 1;
            index = (head + tail) / 2;
        } else {
            tail = index - 1;
            index = (head + tail) / 2;
        }
    }
    return where.end();
}

int main () {
    vector<int> unordered;
    unordered.push_back(3);
    unordered.push_back(7);
    unordered.push_back(2);
    unordered.push_back(4);
    unordered.push_back(9);
    unordered.push_back(8);
    unordered.push_back(3);
    vector<int> ordered;
    unordered.push_back(3);
    unordered.push_back(4);
    unordered.push_back(5);
    unordered.push_back(6);
    unordered.push_back(7);
    unordered.push_back(8);
    unordered.push_back(9);
    auto notFound_1 = orderSearch<int>(unordered, 10);
    auto notFound_2 = minBinarySearch<int>(ordered, 10);
    assert(notFound_1 == unordered.end());
    assert(notFound_2 == ordered.end());
    assert(*orderSearch<int>(unordered, 2) == 2);
}