//
// Created by claim on 16-10-6.
//

#include <cassert>
#include "binaryTree.h"

int main () {
    binaryTree<int> *tree = new binaryTree<int>(8);
    tree->addToLeft(3);
    binaryTree<int> *ten = tree->addToRight(10);
    assert(tree->isCompleteBinaryTree());
    tree->searchData(3)[0]->addToRight(5);
    tree->searchData(3)[0]->addToLeft(2);
    assert(tree->isCompleteBinaryTree());
    tree->searchData(2)[0]->addToLeft(1);
    ten->addToLeft(9)->addToRight(3);
    ten->addToRight(11)->addToRight(15);
    tree->printAllElements();
    tree->preOrderTraversal();
    tree->inOrderTraversal();
    assert(tree->getHeight() == 4);
    assert(!tree->isCompleteBinaryTree());
    assert(tree->getWidth() == 4);
    assert(tree->countWithDegree(2) == 3);
    assert(tree->countWithDegree(1) == 3);
    assert(tree->countWithDegree(0) == 4);
    assert(tree->findMax() == 15);
    tree->deleteAllLeaves();
    tree->printAllElements();
    tree->exchangeLeftAndRight();
    tree->printAllElements();
    ten->printAllElements();
    recycleBinaryTree(tree);
    int pre[] = {
            8, 3, 2, 1, 5, 10, 9, 3, 11, 15
    };
    int in[] = {
            1, 2, 3, 5, 8, 9, 3, 10, 11, 15
    };
    int post[] = {
            1, 2, 5, 3, 3, 9, 15, 11, 10, 8
    };
    tree = binaryTree<int>::generateTreeByPreIn(vector<int>(pre, pre + 10),
                                                vector<int>(in, in + 10));
    putchar('\n');
    tree->preOrderTraversal();
    tree->inOrderTraversal();
    tree->postOrderTraversal();
    recycleBinaryTree(tree);
    tree = binaryTree<int>::generateTreeByInPost(
            vector<int>(in, in + 10),
            vector<int>(post, post + 10)
    );
    putchar('\n');
    tree->preOrderTraversal();
    tree->inOrderTraversal();
    tree->postOrderTraversal();
    recycleBinaryTree(tree);
    return 0;
}