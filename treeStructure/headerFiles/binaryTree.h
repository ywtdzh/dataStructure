//
// Created by claim on 16-10-6.
//

#ifndef DATASTRUCTURE_BINARYTREE_H
#define DATASTRUCTURE_BINARYTREE_H

#include <iostream>
#include <vector>
#include <exception>
#include <queue>

using namespace std;

template<typename D>
class binaryTree;

template<typename D>
void recycleBinaryTree (binaryTree<D> *tree);

template<typename D>
class binaryTree {
    binaryTree<D> *leftTree;
    binaryTree<D> *rightTree;
    binaryTree<D> *parentTree;
protected:
    D data;

    const void printHandler () const;

    void recycleHandler ();

public:
    binaryTree (const D data, binaryTree *parent = nullptr);

    binaryTree<D> *getLeft ();

    binaryTree<D> *getRight ();

    binaryTree<D> *addToLeft (D data);

    binaryTree<D> *addToRight (D data);

    binaryTree<D> *deleteLeft ();

    binaryTree<D> *deleteRight ();

    binaryTree<D> &getRootTree ();

    const D getData () const;

    binaryTree<D> *setData (const D data);

    vector<binaryTree<D> *> searchData (const D data);

    const void printAllElements () const;

    friend void recycleBinaryTree<D> (binaryTree<D> *tree);

    const int countWithDegree (const int degree);

    const int getHeight ();

    const int getWidth ();

    const D findMax () const;

    binaryTree<D> *exchangeLeftAndRight ();

    binaryTree<D> *deleteAllLeaves ();

    bool isCompleteBinaryTree ();

    binaryTree (const binaryTree &) = delete;

    binaryTree &operator= (const binaryTree &)= delete;
};


inline const int max (int a, int b) {
    return a > b ? a : b;
}

template<typename D>
binaryTree<D> *binaryTree<D>::deleteAllLeaves () {
    queue<binaryTree<D> *> nodeQueue;
    if (leftTree)
        nodeQueue.push(leftTree);
    if (rightTree)
        nodeQueue.push(rightTree);
    while (nodeQueue.size()) {
        queue<binaryTree<D> *> temp;
        while (nodeQueue.size()) {
            auto currentNode = nodeQueue.front();
            nodeQueue.pop();
            if (currentNode->leftTree && (!currentNode->leftTree->leftTree && !currentNode->leftTree->rightTree)) {
                delete currentNode->leftTree;
                currentNode->leftTree = nullptr;
            }
            if (currentNode->rightTree && (!currentNode->rightTree->leftTree && !currentNode->rightTree->rightTree)) {
                delete currentNode->rightTree;
                currentNode->rightTree = nullptr;
            }
            if (currentNode->leftTree)
                temp.push(currentNode->leftTree);
            if (currentNode->rightTree)
                temp.push(currentNode->rightTree);
        }
        nodeQueue = temp;
    }
    return this;
}

template<typename D>
bool binaryTree<D>::isCompleteBinaryTree () {
    queue<binaryTree<D> *> nodeQueue;
    bool lackChild = false;
    if (leftTree)
        nodeQueue.push(leftTree);
    if (rightTree)
        nodeQueue.push(rightTree);
    while (nodeQueue.size()) {
        queue<binaryTree<D> *> temp;
        while (nodeQueue.size()) {
            auto currentNode = nodeQueue.front();
            nodeQueue.pop();
            if (currentNode->leftTree)
                temp.push(currentNode->leftTree);
            if (currentNode->rightTree)
                temp.push(currentNode->rightTree);
            if (lackChild && (currentNode->leftTree || currentNode->rightTree))
                return false;
            if (!lackChild && (!currentNode->leftTree || !currentNode->rightTree))
                lackChild = true;
        }
        nodeQueue = temp;
    }
    return true;
}

template<typename D>
binaryTree<D> *binaryTree<D>::exchangeLeftAndRight () {
    auto temp = leftTree;
    leftTree = rightTree;
    rightTree = temp;
    return this;
}

template<typename D>
const int binaryTree<D>::getWidth () {
    queue<binaryTree<D> *> nodeQueue;
    int width = 0;
    if (leftTree)
        nodeQueue.push(leftTree);
    if (rightTree)
        nodeQueue.push(rightTree);
    while (nodeQueue.size()) {
        width = max<int>(width, nodeQueue.size());
        queue<binaryTree<D> *> temp;
        while (nodeQueue.size()) {
            auto currentNode = nodeQueue.front();
            nodeQueue.pop();
            if (currentNode->leftTree)
                temp.push(currentNode->leftTree);
            if (currentNode->rightTree)
                temp.push(currentNode->rightTree);
        }
        nodeQueue = temp;
    }
    return width;
}

template<typename D>
const D binaryTree<D>::findMax () const {
    queue<binaryTree<D> *> nodeQueue;
    D maxData = INT32_MIN;
    if (leftTree)
        nodeQueue.push(leftTree);
    if (rightTree)
        nodeQueue.push(rightTree);
    while (nodeQueue.size()) {
        queue<binaryTree<D> *> temp;
        while (nodeQueue.size()) {
            auto currentNode = nodeQueue.front();
            maxData = max<D>(maxData, currentNode->data);
            nodeQueue.pop();
            if (currentNode->leftTree)
                temp.push(currentNode->leftTree);
            if (currentNode->rightTree)
                temp.push(currentNode->rightTree);
        }
        nodeQueue = temp;
    }
    return maxData;
}

template<typename D>
const int binaryTree<D>::getHeight () {
    int height = 0;
    if (leftTree)
        height = max(height, leftTree->getHeight() + 1);
    if (rightTree)
        height = max(height, rightTree->getHeight() + 1);
    if (!leftTree && !rightTree)
        height = 1;
    return height;
}

template<typename D>
const int binaryTree<D>::countWithDegree (const int degree) {
    if (degree > 2 || degree < 0)
        throw invalid_argument("Argument fault");
    switch (degree) {
        case 0:
            if (leftTree)
                if (rightTree)
                    return leftTree->countWithDegree(0) + rightTree->countWithDegree(0);
                else
                    return leftTree->countWithDegree(0);
            else if (rightTree)
                return rightTree->countWithDegree(0);
            else
                return 1;
        case 1:
            if (leftTree)
                if (rightTree)
                    return leftTree->countWithDegree(1) + rightTree->countWithDegree(1);
                else
                    return leftTree->countWithDegree(1) + 1;
            else if (rightTree)
                return rightTree->countWithDegree(1) + 1;
            else
                return 0;
        case 2:
            if (leftTree)
                if (rightTree)
                    return leftTree->countWithDegree(2) + rightTree->countWithDegree(2) + 1;
                else
                    return leftTree->countWithDegree(2);
            else if (rightTree)
                return rightTree->countWithDegree(2);
            else
                return 0;
    }
}

template<typename D>
binaryTree<D>::binaryTree (const D data, binaryTree *parent) {
    this->data = data;
    this->parentTree = parent;
    leftTree = rightTree = nullptr;
}

template<typename D>
binaryTree<D> *binaryTree<D>::addToLeft (D data) {
    if (!leftTree) {
        this->leftTree = new binaryTree(data, this);
        return leftTree;
    } else {
        return this;
    }
}

template<typename D>
binaryTree<D> *binaryTree<D>::addToRight (D data) {
    if (!rightTree) {
        this->rightTree = new binaryTree(data, this);
        return rightTree;
    } else {
        return this;
    }

}

template<typename D>
binaryTree<D> *binaryTree<D>::getLeft () {
    return this->leftTree;
}

template<typename D>
binaryTree<D> *binaryTree<D>::getRight () {
    return this->rightTree;
}

template<typename D>
binaryTree<D> *binaryTree<D>::deleteLeft () {
    this->leftTree->recycleHandler();
    delete leftTree;
    leftTree = nullptr;
    return this;
}

template<typename D>
binaryTree<D> *binaryTree<D>::deleteRight () {
    this->rightTree->recycleHandler();
    delete rightTree;
    rightTree = nullptr;
    return this;
}

template<typename D>
binaryTree<D> *binaryTree<D>::setData (const D data) {
    this->data = data;
    return this;
}

template<typename D>
vector<binaryTree<D> *> binaryTree<D>::searchData (const D data) {
    vector<binaryTree<D> *> result;
    if (this && data == this->data) {
        result.push_back(this);
    }
    if (leftTree) {
        vector<binaryTree<D> *> leftResult = leftTree->searchData(data);
        result.insert(result.begin(), leftResult.begin(), leftResult.end());
    }
    if (rightTree) {
        vector<binaryTree<D> *> rightResult = rightTree->searchData(data);
        result.insert(result.begin(), rightResult.begin(), rightResult.end());
    }
    return result;
}

template<typename D>
const D binaryTree<D>::getData () const {
    return data;
}

template<typename D>
void recycleBinaryTree (binaryTree<D> *tree) {
    binaryTree<D> *root = &tree->getRootTree();
    root->recycleHandler();
    delete root;
}

template<typename D>
binaryTree<D> &binaryTree<D>::getRootTree () {
    binaryTree<D> *rootPtr = this;
    while (rootPtr->parentTree != nullptr) {
        rootPtr = rootPtr->parentTree;
    }
    return *rootPtr;
}

template<typename D>
const void binaryTree<D>::printHandler () const {
    if (this->leftTree) {
        this->leftTree->printHandler();
    }
    cout << this->data << '\t';
    if (this->rightTree) {
        this->rightTree->printHandler();
    }
}

template<typename D>
const void binaryTree<D>::printAllElements () const {
    printHandler();
    putchar('\n');
}

template<typename D>
void binaryTree<D>::recycleHandler () {  //Must called by root tree
    if (leftTree) {
        if (leftTree->leftTree || leftTree->rightTree) {
            leftTree->recycleHandler();
        }
        delete leftTree;
        leftTree = nullptr;
    }
    if (rightTree) {
        if (rightTree->leftTree || rightTree->rightTree) {
            rightTree->recycleHandler();
        }
        delete rightTree;
        rightTree = nullptr;
    }
    return;
}

#endif //DATASTRUCTURE_BINARYTREE_H
