//
// Created by claim on 16-10-7.
//

#include <assert.h>
#include "queue.h"

int main (int argc, char **argv) {
    {
        linkedQueue<int> Q;
        Q.enQueue(5);
        cout << Q;
        assert(Q.deQueue() == 5);
        Q.enQueue(9);
        Q.enQueue(3);
        Q.enQueue(2);
        Q.enQueue(5);
        assert(Q.getLength() == 4);
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
    }
    {
        orderedQueue<int> Q(5);
        assert(Q.getLength() == 0);
        assert(Q.peek() == INT32_MIN); //Should fail
        Q.enQueue(8).enQueue(4);
        Q.enQueue(7);
        Q.enQueue(1);
        Q.enQueue(2); //8 4 7 1 2
        assert(Q.getLength() == 5);
        Q.enQueue(6); //Should Fail
        assert(Q.peek() == 8);
        assert(Q.deQueue() == 8);
        assert(Q.deQueue() == 4);
        Q.enQueue(0); //7 1 2 0
        cout << Q;
        assert(Q.getLength() == 4);
        Q.deQueue(); //7
        Q.deQueue(); //1
        Q.deQueue(); //2
        assert(Q.deQueue() == 0);
        Q.enQueue(1);
        cout << Q;
        assert(Q.getLength() == 1);
    }
    return 0;
}