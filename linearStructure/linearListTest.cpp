//
// Created by claim on 16-9-11.
//
#include "linkedList.h"

int main() {
    linkedList *list = createList(1);
    addNode(list, 0, 4);
    addNode(list, 4, 4);
    addNode(list, 3, 4);
    addNode(list, 3, 4);
    addNode(list, 6, 4);
    printList(list);
    deleteNode(list, 3);
    printList(list);
}

