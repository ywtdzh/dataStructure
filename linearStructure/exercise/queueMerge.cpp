//
// Created by claim on 16-10-22.
//
//T14 Input integer number under 10
#include "queue.h"
#include <sstream>

template<typename T>
void mergeQueue (linkedQueue<T> &target, linkedQueue<T> source) {
    while (source.getLength()) {
        target.enQueue(source.peek());
        source.deQueue();
    }
}

int main () {
    linkedQueue<int> queues[10];
    linkedQueue<int> result;
    int data = 0;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfor-loop-analysis"
    //disable inspect for no-changed variables for loop
    while (data > -1 && data < 10) {
        string input;
        cin >> input;
        if (stringstream(input) >> data && data > -1 && data < 10) {
            queues[data].enQueue(data);
        } else {
            break;
        }
    }
#pragma clang diagnostic pop
    for (int i = 0; i < 10; ++i) {
        if (queues[i].getLength()) {
            mergeQueue(result, queues[i]);
        }
    }
    while (result.getLength()) {
        cout << result.peek() << '\t';
        result.deQueue();
    }
}