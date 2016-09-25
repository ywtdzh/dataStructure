//
// Created by claim on 16-9-25.
//

#include <cstdlib>
#include <iostream>
#include <climits>

using namespace std;

#include "doubleWayCycleChain.h"

doubleWayCycleChain::doubleWayCycleChain(data source) {
    list = (chain *) malloc(sizeof(chain));
    list->content = INT_MAX;
    list->next = (chain *) malloc(sizeof(chain));
    list->next->content = source;
    list->next->next = list;
    list->next->prev = list;
    list->prev = list->next;
}

void doubleWayCycleChain::printChain() {
    node *head = list;
    if (list->next == head) {
        cout << "已经没有元素可以输出了...\n";
        return;
    }
    while (list->next != head) {
        list = list->next;
        cout << list->content << '\t';
    }
    list = head;
    cout << endl;
}

void doubleWayCycleChain::deleteOneByValue(data value) {
    node *head = list;
    while (1) {
        if (list->next->content == value) {
            node *temp = list->next;
            list->next = list->next->next;
            list->next->prev = list;
            free(temp);
            break;
        }
        if (list->next != head)
            list = list->next;
        else {
            cout << "没有找到指定的元素\n";
            break;
        }
    }
    list = head;
}

void doubleWayCycleChain::addNode(data source) {
    list->prev->next = (chain *) malloc(sizeof(chain));
    list->prev->next->content = source;
    list->prev->next->next = list;
    list->prev->next->prev = list->prev;
    list->prev = list->prev->next;
}