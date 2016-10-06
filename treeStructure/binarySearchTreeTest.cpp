//
// Created by claim on 16-10-5.
//

#include "binarySearchTree.h"
#include <cassert>

int main () {
    binarySearchTree<int> *tree = new binarySearchTree<int>(8);
    assert(tree->getData() == 8);
    tree->printAllElements();
    tree->addData(3);
    tree->addData(10);
    tree->addData(3); //Repetitive data should never be inserted
    tree->addData(2);
    tree->addData(5);
    tree->addData(9);
    tree->addData(1);
    tree->addData(11);
    tree->addData(15);
    tree->printAllElements();
    const binarySearchTree<int> *three = tree->getLeftTree();
    assert(three->getData() == 3);
    assert(tree->getRootTree().getData() == 8);
    tree = tree->removeData(8);
    tree->printAllElements();
    tree = tree->removeData(5);
    tree->printAllElements();
    tree->getLeftTree()->printAllElements();
    recycleBinaryTree(tree);
    return 0;
}