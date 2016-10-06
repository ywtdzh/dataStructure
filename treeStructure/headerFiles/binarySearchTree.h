//
// Created by claim on 16-10-5.
//

#ifndef DATASTRUCTURE_BINARYTREE_H
#define DATASTRUCTURE_BINARYTREE_H

#include <iostream>

using namespace std;

template<typename D>
class binarySearchTree;

template<typename D>
void recycleBinaryTree (binarySearchTree<D> *tree);

template<typename D>
class binarySearchTree {
    D data;
    binarySearchTree<D> *leftTree;
    binarySearchTree<D> *rightTree;
    binarySearchTree<D> *parentTree;

    binarySearchTree<D> *findData (const D data);


    void addDataHandler (const D data); //Must called by root tree
    binarySearchTree<D> *rmDataHandler (const D data); //Must called by root tree,return root
    const void printHandler () const;

    void recycleHandler (); //Must called by root tree

public:
    binarySearchTree (const D data, binarySearchTree *parent = nullptr);

    const binarySearchTree<D> *getParent ();

    const binarySearchTree<D> *getLeftTree ();

    const binarySearchTree<D> *getRightTree ();

    binarySearchTree<D> &getRootTree ();

    const binarySearchTree<D> *addData (const D data);

    binarySearchTree<D> *removeData (const D data);

    const void printAllElements () const;

    const D getData () const;

    friend void recycleBinaryTree<> (binarySearchTree<D> *tree);

    binarySearchTree (const binarySearchTree &) = delete;

    binarySearchTree &operator= (const binarySearchTree &) = delete;
};

template<typename D>
void recycleBinaryTree (binarySearchTree<D> *tree) {
    binarySearchTree<D> *root = &tree->getRootTree();
    root->recycleHandler();
    delete root;
}

template<typename D>
binarySearchTree<D>::binarySearchTree (const D data, binarySearchTree *parent) {
    leftTree = rightTree = nullptr;
    parentTree = nullptr;
    this->data = data;
}

template<typename D>
const binarySearchTree<D> *binarySearchTree<D>::getParent () {
    return parentTree;
}

template<typename D>
const binarySearchTree<D> *binarySearchTree<D>::getLeftTree () {
    return leftTree;
}

template<typename D>
const binarySearchTree<D> *binarySearchTree<D>::getRightTree () {
    return rightTree;
}

template<typename D>
binarySearchTree<D> &binarySearchTree<D>::getRootTree () {
    binarySearchTree<D> *rootPtr = this;
    while (rootPtr->parentTree != nullptr) {
        rootPtr = rootPtr->parentTree;
    }
    return *rootPtr;
}

template<typename D>
binarySearchTree<D> *binarySearchTree<D>::findData (const D data) {
    if (this->data > data) {
        if (this->leftTree) {
            return this->leftTree->findData(data);
        } else {
            return nullptr;
        }
    } else if (this->data < data) {
        if (this->rightTree) {
            return this->rightTree->findData(data);
        } else {
            return nullptr;
        }
    } else {
        return this;
    }
}

template<typename D>
void binarySearchTree<D>::addDataHandler (const D data) {
    //Supposed call by root tree
    if (this->data == data) {
        return;
    } else if (this->data > data) {
        if (this->leftTree) {
            this->leftTree->addDataHandler(data);
        } else {
            this->leftTree = new binarySearchTree(data, this);
            this->leftTree->parentTree = this;
            return;
        }
    } else { //this->data < data
        if (this->rightTree) {
            this->rightTree->addDataHandler(data);
        } else {
            this->rightTree = new binarySearchTree(data, this);
            this->rightTree->parentTree = this;
            return;
        }
    }
}

template<typename D>
const binarySearchTree<D> *binarySearchTree<D>::addData (const D data) {
    binarySearchTree<D> *root = &this->getRootTree();
    root->addDataHandler(data);
    return root;
}

template<typename D>
binarySearchTree<D> *binarySearchTree<D>::rmDataHandler (const D data) {
    //Supposed call by root tree
    binarySearchTree<D> *target = findData(data);
    if (target) {
        if (target->parentTree) {
            if (target->data < target->parentTree->data) {
                if (target->rightTree) {
                    binarySearchTree<D> *leaf = target->parentTree->leftTree = target->rightTree;
                    while (leaf->leftTree) {
                        leaf = leaf->leftTree;
                    }
                    leaf->leftTree = target->leftTree;
                    leaf->leftTree->parentTree = leaf;
                    delete target;
                } else {
                    target->parentTree->leftTree = target->leftTree;
                    if (target->leftTree) {
                        target->leftTree->parentTree = target->parentTree;
                    }
                    delete target;
                }
            } else {
                if (target->leftTree) {
                    binarySearchTree<D> *leaf = target->parentTree->rightTree = target->leftTree;
                    while (leaf->rightTree) {
                        leaf = leaf->rightTree;
                    }
                    leaf->rightTree = target->rightTree;
                    target->rightTree->parentTree = leaf;
                    delete target;
                } else {
                    target->parentTree->rightTree = target->rightTree;
                    if (target->rightTree) {
                        target->rightTree->parentTree = target->parentTree;
                    }
                    delete target;
                }
            }
        } else { //target is root tree
            if (target->leftTree) {
                target->leftTree->parentTree = nullptr;
                binarySearchTree<D> *root = target->leftTree;
                binarySearchTree<D> *leaf = target->leftTree;
                while (leaf->rightTree) {
                    leaf = leaf->rightTree;
                }
                leaf->rightTree = target->rightTree;
                target->rightTree->parentTree = leaf;
                delete target;
                return root;
            } else if (target->rightTree) {
                target->rightTree->parentTree = nullptr;
                binarySearchTree<D> *root = target->rightTree;
                delete target;
                return root;
            } else {
                delete target;
                return nullptr;
            }
        }
    } else { //target doesn't exist
        //doNothing
    }
    return this;
}

template<typename D>
binarySearchTree<D> *binarySearchTree<D>::removeData (const D data) {
    binarySearchTree<D> *root = &this->getRootTree();
    root = root->rmDataHandler(data);
    return root;
}

template<typename D>
const void binarySearchTree<D>::printHandler () const {
    if (this->leftTree) {
        this->leftTree->printHandler();
    }
    cout << this->data << '\t';
    if (this->rightTree) {
        this->rightTree->printHandler();
    }
}

template<typename D>
const void binarySearchTree<D>::printAllElements () const {
    printHandler();
    putchar('\n');
}

template<typename D>
const D binarySearchTree<D>::getData () const {
    return data;
}

template<typename D>
void binarySearchTree<D>::recycleHandler () {  //Must called by root tree
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