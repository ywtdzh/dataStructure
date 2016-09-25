//
// Created by claim on 16-9-11.
//

#include <cstdio>
#include <climits>
#include "linkedList.h"

#include <stack>

using namespace std;
linkedList *createList(data content) {
    linkedList *list = (linkedList *) malloc(sizeof(node));
    list->next = NULL;
    list->content = content;
    return list;
}

linkedList *addNode(linkedList *list, data content, data target) {
    if (!list) return list;
    node *current = list;
    while (current->next != NULL && current->content != target) {
        current = current->next;
    }
    if (current->content == target) {
        node *tail = current->next;
        current->next = (node *) malloc(sizeof(node));
        current->next->content = content;
        current->next->next = tail;
    } else { //current->next == NULL
        current->next = (node *) malloc(sizeof(node));
        current->next->next = NULL;
        current->next->content = content;
    }
    return list;
}

linkedList *deleteNode(linkedList *list, data target) {
    if (!list) return list;
    node *current = list;
    if (current->content == target) {
        list = deleteNode(current->next, target);
        free(current);
        return list;
    }
    while (current->next != NULL && current->next->content != target) {
        current = current->next;
    }
    if (current->next) {
        node *deleted = current->next;
        current->next = deleted->next;
        free(deleted);
        deleteNode(current, target);
    }
    return list;
}

void printList(linkedList *list) {
    node *current = list;
    while (current) {
        printf("%d ", current->content);
        current = current->next;
    }
    putchar('\n');
}

linkedList *reverseList(linkedList *currentNode) {
    stack<data> temp;
    while (currentNode) {
        temp.push(currentNode->content);
        currentNode = currentNode->next;
    }
    linkedList *list = createList(temp.top());
    temp.pop();
    while (!temp.empty()) {
        addNode(list, temp.top(), INT_MAX);
        temp.pop();
    }
    return list;
}