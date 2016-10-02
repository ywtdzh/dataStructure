//
// Created by claim on 16-9-12.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H

//Template functions' definition must be in header files! Currently no compilers achieve the keyword "export"
const int MAX = 20;

#include <cstdio>
#include <cstdlib>

template<typename data>
class orderStack {
    data *stack;
    int topPosition;
public:
    orderStack(int size = MAX);

    orderStack &push(data source);

    orderStack &pop(data *target = 0);

    data top();

    int size();

    bool empty();

    ~orderStack();
};

template<typename data>
class linkedStack {
    typedef struct node {
        node *next;
        data content;
    } node;
    node *head;
    node *topPosition;
    int dataSize;
public:
    linkedStack(int i = 0);

    linkedStack &push(data source);

    linkedStack &pop(data *target = 0);

    data top();

    int size();

    bool empty();

    ~linkedStack();
};


//Ordered stack
template<typename data>
orderStack<data>::orderStack(int size) {
    topPosition = -1;
    stack = new data[size];
}

template<typename data>
bool orderStack<data>::empty() {
    return topPosition == -1;
}

template<typename data>
int orderStack<data>::size() {
    return topPosition + 1;
}

template<typename data>
orderStack<data> &orderStack<data>::pop(data *target) {
    if (!empty()) {
        target ? (*target = stack[topPosition]) : 0;
        topPosition--;
    } else {
        printf("The Stack is Empty\n");
    }
    return *this;
}

template<typename data>
orderStack<data> &orderStack<data>::push(data source) {
    if (topPosition < MAX - 1) {
        topPosition++;
        stack[topPosition] = source;
        return *this;
    } else {
        printf("The Stack is Full\n");
    }
    return *this;
}

template<typename data>
data orderStack<data>::top() {
    if (topPosition > -1)
        return stack[topPosition];
    else {
        printf("The Stack is Empty\n");
    }
}

template<typename data>
orderStack<data>::~orderStack() {
    delete[](stack);
}

//Linked stack

template<typename data>
linkedStack<data>::linkedStack(int) {
    head = new node;
    head->next = nullptr;
    topPosition = head;
    dataSize = 0;
}

template<typename data>
bool linkedStack<data>::empty() {
    return dataSize == 0;
}

template<typename data>
int linkedStack<data>::size() {
    return dataSize;
}

template<typename data>
data linkedStack<data>::top() {
    return empty() ? printf("The Stack is Empty\n") : topPosition->content;
}

template<typename data>
linkedStack<data> &linkedStack<data>::push(data source) {
    topPosition->next = new node;
    topPosition = topPosition->next;
    topPosition->content = source;
    topPosition->next = nullptr;
    dataSize++;
    return *this;
}

template<typename data>
linkedStack<data> &linkedStack<data>::pop(data *target) {
    target ? (*target = topPosition->content) : 0;
    node *temp = head;
    if (!head->next) {
        printf("The Stack is Empty\n");
        return *this;
    }
    while (temp->next != topPosition) {
        temp = temp->next;
    }
    delete (temp->next);
    topPosition = temp;
    topPosition->next = nullptr;
    dataSize--;
    return *this;
}

template<typename data>
linkedStack<data>::~linkedStack() {
    while (!empty()) {
        pop();
    }
    delete (head);
}

#endif //DATASTRUCTURE_STACK_H
