//
// Created by claim on 16-9-17.
//

#include "sqList.h"
#include <iostream>
using namespace std;

int main(){
    //无序表测试
    sqList list(UNORDERED);
    list.addElement(4);
    list.addElement(3);
    list.addElement(6);
    list.addElement(17);
    list.addElement(2);
    list.addElement(2);
    list.addElement(2);
    list.addElement(6);
    list.printList();
    list.removeAllByValue(2);
    list.printList();
    list.addElement(5);
    list.printList();
    cout<<*list.getElement(3)<<endl<<list.getOutMin()<<endl;
    list.printList();
    list.removeAllByValue(2);
    //有序表测试
    sqList orderedList(ORDERED);
    orderedList.addElement(5);
    orderedList.addElement(2);
    orderedList.addElement(3);
    orderedList.addElement(8);
    orderedList.addElement(1);
    orderedList.printList();
    orderedList.removeByInterval(2,5);
    orderedList.printList();
}