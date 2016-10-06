//
// Created by claim on 16-10-6.
//

#ifndef DATASTRUCTURE_BINARYTREE_H
#define DATASTRUCTURE_BINARYTREE_H

#include <iostream>
#include <vector>

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

    binaryTree (const binaryTree &) = delete;

    binaryTree &operator= (const binaryTree &)= delete;
};

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
