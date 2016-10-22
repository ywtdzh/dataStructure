//
// Created by claim on 16-10-7.
//

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H

#include <memory>
#include <iostream>
#include <exception>

using namespace std;

template<typename D>
class linkedQueue;

//template <typename D>
//class linkedQueue<D>::node;

template<typename D>
ostream &operator<< (ostream &out, const typename linkedQueue<D>::node &source);

template<typename D>
ostream &operator<< (ostream &out, const linkedQueue<D> &source);


template<typename D>
class linkedQueue {
    class node {
        //Just accessed by class linkedQueue <D>
    public:  //For make_shared
        D data;
        shared_ptr<node> nextNode;

        node (D data);

        node (const node &source);

        const node &operator= (const node &source);
        //Auto Destruct
    };

    shared_ptr<node> head;
    shared_ptr<node> tail;

    void init (const linkedQueue<D> &source);

public:
    linkedQueue ();

    linkedQueue (const linkedQueue<D> &source);

    const linkedQueue<D> &operator= (const linkedQueue<D> &source);

    linkedQueue<D> &enQueue (D data);

    const D deQueue ();

    const D &peek ();

    const int getLength ();

    friend ostream &operator<<<D> (ostream &out, const linkedQueue<D>::node &source);

    friend ostream &operator<<<D> (ostream &out, const linkedQueue<D> &source);

    //Auto Destruct
};


template<typename D>
linkedQueue<D>::node::node (D data):data(data), nextNode(nullptr) {}

template<typename D>
//Linked Copy
linkedQueue<D>::node::node (const linkedQueue<D>::node &source):data(source.data) {
    if (source.nextNode) {
        nextNode = make_shared<linkedQueue<D>::node>(*source.nextNode);
    } else {
        nextNode = nullptr;
    }
}

template<typename D>
//Linked Copy
const typename linkedQueue<D>::node &linkedQueue<D>::node::operator= (const linkedQueue<D>::node &source) {
    data = source.data;
    nextNode = make_shared<linkedQueue<D>::node>(*source.nextNode);
    return *this;
}

template<typename D>
ostream &operator<< (ostream &out, const typename linkedQueue<D>::node &data) {
    out << data.data << '\t';
    return out;
}

template<typename D>
linkedQueue<D>::linkedQueue ():head(nullptr), tail(nullptr) {}

template<typename D>
void linkedQueue<D>::init (const linkedQueue<D> &source) {
    if (source.head) {
        head = make_shared<node>(*source.head); //Call copy constructor for node<D>
        auto temp = head;
        while (temp->nextNode) { //Set tail
            temp = temp->nextNode;
        }
        tail = temp;
    } else {  //Source is empty
        head = nullptr;
        tail = nullptr;
    }
}

template<typename D>
linkedQueue<D>::linkedQueue (const linkedQueue<D> &source) {
    init(source);
}

template<typename D>
const linkedQueue<D> &linkedQueue<D>::operator= (const linkedQueue<D> &source) {
    init(source);
    return *this;
}


template<typename D>
linkedQueue<D> &linkedQueue<D>::enQueue (D data) {
    if (tail) {
        tail->nextNode = make_shared<node>(data);
        tail = tail->nextNode;
        tail->nextNode = nullptr;
    } else { //Queue is empty
        head = tail = make_shared<node>(data);
    }
    return *this;
}

template<typename D>
const D linkedQueue<D>::deQueue () {
    if (!head) {
        cout << "队列中无元素" << endl;
        throw exception();
    }
    D result = head->data;
    head = head->nextNode;
    if (!head) {
        tail = nullptr;
    }
    return result;
}

template<typename D>
const D &linkedQueue<D>::peek () {
    if (!head) {
        cout << "队列中无元素" << endl;
        throw exception();
    }
    return head->data;
}

template<typename D>
const int linkedQueue<D>::getLength () {
    int length = 0;
    auto temp = head;
    while (temp) {
        length++;
        temp = temp->nextNode;
    }
    return length;
}

template<typename D>
ostream &operator<< (ostream &out, const linkedQueue<D> &source) {
    auto temp = source.head;
    while (temp) {
        operator<<<D>(out, *temp);
        temp = temp->nextNode;
    }
    out << '\n';
    return out;
}

//Ordered Queue
template<typename D>
class orderedQueue;

template<typename D>
ostream &operator<< (ostream &out, const orderedQueue<D> &queue);

template<typename D>
class orderedQueue {
    const int limit;
    D *queue;
    int head, tail;

    void init (const orderedQueue<D> &source);
public:
    orderedQueue (const int limit = 21);

    orderedQueue (const orderedQueue<D> &);

    const int getLength () const;

    const orderedQueue<D> &operator= (const orderedQueue<D> &);

    orderedQueue<D> &enQueue (const D data);

    const D deQueue ();

    const D peek () const;

    friend ostream &operator<<<> (ostream &out, const orderedQueue<D> &);

    ~orderedQueue ();
};

template<typename D>
orderedQueue<D>::orderedQueue (const int limit) : limit(limit > 0 ? limit + 1 : 1), head(0), tail(0) {
    queue = new int[limit];
}

template<typename D>
void orderedQueue<D>::init (const orderedQueue<D> &source) {
    limit = source.limit;
    queue = new int[limit];
    head = 0;
    tail = source.getLength();
    for (int i = 0; i < tail; ++i) {
        int position = head + i >= limit ?
                       head + i - limit :
                       head + i;
        queue[i] = source.queue[position];
    }
}

template<typename D>
orderedQueue<D>::orderedQueue (const orderedQueue<D> &source) {
    init();
}

template<typename D>
const orderedQueue<D> &orderedQueue<D>::operator= (const orderedQueue<D> &) {
    init();
    return *this;
}

template<typename D>
const int orderedQueue<D>::getLength () const {
    return head > tail ?
           tail + limit - head :
           tail - head;
}

template<typename D>
orderedQueue<D> &orderedQueue<D>::enQueue (const D data) {
    if (tail + 1 != head && tail + 1 - limit != head) {
        queue[tail] = data;
        tail++;
        if (tail >= limit) {
            tail -= limit;
        }
    } else {
        cout << "Failure to enqueue : The queue has been full\n";
    }
    return *this;
}

template<typename D>
const D orderedQueue<D>::deQueue () {
    if (head != tail) {
        D result = queue[head];
        head++;
        if (head >= limit) {
            head -= limit;
        }
        return result;
    } else {
        cout << "Failure to dequeue : The queue is empty\n";
        throw exception();
    }
}

template<typename D>
const D orderedQueue<D>::peek () const {
    if (head != tail) {
        return queue[head];
    } else {
        cout << "Failure to peek : The queue is empty\n";
        throw exception();
    }
}

template<typename D>
ostream &operator<< (ostream &out, const orderedQueue<D> &queue) {
    const int length = queue.getLength();
    if (queue.head < queue.tail) {
        for (int i = 0; i < length; ++i) {
            out << queue.queue[queue.head + i];
        }
    } else {
        for (int i = 0; i < length; ++i) {
            int position = queue.head + i >= queue.limit ?
                           queue.head + i - queue.limit :
                           queue.head + i;
            out << queue.queue[position] << '\t';
        }
    }
    out << endl;
    return out;
}

template<typename D>
orderedQueue<D>::~orderedQueue () {
    delete[] queue;
}

#endif //DATASTRUCTURE_QUEUE_H
