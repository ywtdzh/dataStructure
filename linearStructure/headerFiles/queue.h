//
// Created by claim on 16-10-7.
//

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H

#include <memory>
#include <iostream>

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
        head = make_shared<node>(*source.head); //Call constructor for node<D>
        auto temp = head;
        while (temp->nextNode) {
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
        return INT32_MIN;
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
        return INT32_MIN;
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

#endif //DATASTRUCTURE_QUEUE_H
