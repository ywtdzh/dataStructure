//
// Created by claim on 16-11-29.
//

#include "AVLTree.h"

int main () {
    AVLTree<int> tree;
    tree.addElement(8);
    tree.addElement(3);
    tree.addElement(2);
    tree.addElement(4);
    tree.addElement(13);
    tree.addElement(17);
    tree.addElement(22);
    tree.addElement(5);
    tree.printElements();
    tree.removeElement(8);
    tree.printElements();
}