//
// Created by claim on 16-10-7.
//

#include <assert.h>
#include "queue.h"

int main (int argc, char **argv) {
    linkedQueue<int> Q;
    Q.enQueue(5);
    cout << Q;
    assert(Q.deQueue() == 5);
    Q.enQueue(9);
    Q.enQueue(3);
    Q.enQueue(2);
    Q.enQueue(5);
    cout << Q;
    assert(Q.deQueue() == 9);
    assert(Q.peek() == 3);
    assert(Q.deQueue() == 3);
    {
        auto Q2 = Q;
        assert(Q2.deQueue() == 2);
        assert(Q2.deQueue() == 5);
        Q2.enQueue(8);
        cout << Q2;
        linkedQueue<int> Q3(Q);
        assert(Q3.deQueue() == 2);
        assert(Q3.deQueue() == 5);
        Q3.enQueue(8);
        cout << Q3;
    }
    cout << Q;
    return 0;
}