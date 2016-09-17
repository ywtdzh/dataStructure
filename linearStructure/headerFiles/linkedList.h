//
// Created by claim on 16-9-11.
//

#ifndef DATASTRUCTURE_LINKEDLIST_H
#define DATASTRUCTURE_LINKEDLIST_H

#include "data.h"
#include <cstdlib>

typedef struct node {
    data content;
    node *next;
} node;

typedef node linkedList;

linkedList *createList(data content);

linkedList *addNode(linkedList *list, data content, data target);

linkedList *deleteNode(linkedList *list,data target);

void printList(linkedList * list);

#endif //DATASTRUCTURE_LINKEDLIST_H
