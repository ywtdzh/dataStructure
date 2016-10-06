//
// Created by claim on 16-10-6.
//

#include <cassert>
#include "binaryTree.h"

int main () {
    binaryTree<int> *tree = new binaryTree<int>(8);
    tree->addToLeft(3);
    binaryTree<int> *ten = tree->addToRight(10);
    tree->searchData(3)[0]->addToRight(5);
    tree->searchData(3)[0]->addToLeft(2);
    tree->searchData(2)[0]->addToLeft(1);
    ten->addToLeft(9)->addToRight(3);
    ten->addToRight(11)->addToRight(15);
    tree->printAllElements();
    assert(tree->searchData(3)[0]->addToLeft(5)->setData(2398)->getData() == 2398);
    tree->printAllElements();
    ten->printAllElements();
    recycleBinaryTree(tree);
    return 0;
}