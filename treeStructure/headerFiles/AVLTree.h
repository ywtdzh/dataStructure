//
// Created by claim on 16-11-29.
//

#ifndef DATASTRUCTURE_AVLTREE_H
#define DATASTRUCTURE_AVLTREE_H

#include <memory>
#include <stack>
#include <iostream>

using namespace std;

template<typename D>
class AVLTree {
    struct AVLNode {
        D data;
        AVLNode *leftNode;
        AVLNode *rightNode;

        AVLNode (const D &data) : data(data) { leftNode = rightNode = nullptr; }

        static void recycleHandler (AVLNode *node) {
            if (node->leftNode) {
                recycleHandler(node->leftNode);
            }
            if (node->rightNode) {
                recycleHandler(node->rightNode);
            }
            delete node;

        }

        AVLNode *LRotate () {
            auto root = rightNode;
            rightNode = root->leftNode;
            root->leftNode = const_cast<AVLNode *>(this);
            return root;
        }

        AVLNode *RRotate () {
            auto root = leftNode;
            leftNode = root->rightNode;
            root->rightNode = const_cast<AVLNode *>(this);
            return root;
        }

        AVLNode *LRRotate () {
            auto root = leftNode->rightNode;
            auto lChild = root->leftNode, rChild = root->rightNode;
            root->leftNode = leftNode;
            root->rightNode = const_cast<AVLNode *>(this);
            root->leftNode->rightNode = lChild;
            root->rightNode->leftNode = rChild;
            return root;
        }

        AVLNode *RLRotate () {
            auto root = rightNode->leftNode;
            auto lChild = root->leftNode, rChild = root->rightNode;
            root->rightNode = rightNode;
            root->leftNode = const_cast<AVLNode *>(this);
            root->leftNode->rightNode = lChild;
            root->rightNode->leftNode = rChild;
            return root;
        }
    };

    AVLNode *root;

    static int getHeight (AVLNode *target) {
        if (target == 0)
            return 0;
        int leftHeight = getHeight(target->leftNode);
        int rightHeight = getHeight(target->rightNode);
        return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }

public:
    AVLTree () : root(nullptr) {};

    int findElement (const D &data);

    int addElement (const D &data);

    int removeElement (const D &data);

    void printElements ();

    ~AVLTree ();
};

template<typename D>
AVLTree<D>::~AVLTree () {
    AVLNode::recycleHandler(root);
}

template<typename D>
int AVLTree<D>::findElement (const D &data) {
    auto current = root;
    while (current) {
        if (current->data > data)
            current = current->leftNode;
        else if (current->data < data)
            current = current->rightNode;
        else
            return 1;
    }
    return 0;
}

template<typename D>
void AVLTree<D>::printElements () {
    auto current = root;
    stack<AVLNode *> routes;
    while (current || !routes.empty()) {
        if (!current) {
            current = routes.top();
            routes.pop();
        } else
            while (current->leftNode) {
                routes.push(current);
                current = current->leftNode;
            }
        cout << current->data << '\t';
        current = current->rightNode;
    }
    cout << endl;
}

template<typename D>
int AVLTree<D>::addElement (const D &data) {
    if (!root) {
        root = new AVLNode(data);
        return 1;
    }
    auto current = root;
    stack<AVLNode *> routes;
    while (current != nullptr) {
        if (data < current->data) {
            routes.push(current);
            current = current->leftNode;
        } else if (data > current->data) {
            routes.push(current);
            current = current->rightNode;
        } else {
            return 0;
        }
    }
    AVLNode *father = nullptr;
    AVLNode *grandFather = nullptr;
    AVLNode *greatGrandFather = nullptr;
    if (!routes.empty()) {
        father = routes.top();
        routes.pop();
    }
    if (!routes.empty()) {
        grandFather = routes.top();
        routes.pop();
    }
    if (!routes.empty()) {
        greatGrandFather = routes.top();
        routes.pop();
    }
    if (data > father->data) {
        current = new AVLNode(data);
        father->rightNode = current;
    } else {
        current = new AVLNode(data);
        father->leftNode = current;
    }
    //Add complete
    do {
        int heightDiff = 0;
        if (grandFather) {
            heightDiff = getHeight(grandFather->rightNode) - getHeight(grandFather->leftNode);
        }
        if (heightDiff < -1 || heightDiff > 1) {
            if (father == grandFather->leftNode && current == father->leftNode) {
                if (greatGrandFather && greatGrandFather->leftNode == grandFather) {
                    greatGrandFather->leftNode = grandFather->RRotate();
                } else if (greatGrandFather && greatGrandFather->rightNode == grandFather) {
                    greatGrandFather->rightNode = grandFather->RRotate();
                } else {
                    root = grandFather->RRotate();
                    return 1;
                }
            }
            if (father == grandFather->rightNode && current == father->leftNode) {
                if (greatGrandFather && greatGrandFather->leftNode == grandFather) {
                    greatGrandFather->leftNode = grandFather->RLRotate();
                    return 1;
                } else if (greatGrandFather && greatGrandFather->rightNode == grandFather) {
                    greatGrandFather->rightNode = grandFather->RLRotate();
                    return 1;
                } else {
                    root = grandFather->RLRotate();
                    return 1;
                }
            }
            if (father == grandFather->leftNode && current == father->rightNode) {
                if (greatGrandFather && greatGrandFather->leftNode == grandFather) {
                    greatGrandFather->leftNode = grandFather->LRRotate();
                    return 1;
                } else if (greatGrandFather && greatGrandFather->rightNode == grandFather) {
                    greatGrandFather->rightNode = grandFather->LRRotate();
                    return 1;
                } else {
                    root = grandFather->LRRotate();
                    return 1;
                }
            }
            if (father == grandFather->rightNode && current == father->rightNode) {
                if (greatGrandFather && greatGrandFather->leftNode == grandFather) {
                    greatGrandFather->leftNode = grandFather->LRotate();
                } else if (greatGrandFather && greatGrandFather->rightNode == grandFather) {
                    greatGrandFather->rightNode = grandFather->LRotate();
                } else {
                    root = grandFather->LRotate();
                }
                return 1;
            }
        }
        //Move up
        current = father;
        father = grandFather;
        grandFather = greatGrandFather;
        if (!routes.empty()) {
            greatGrandFather = routes.top();
            routes.pop();
        } else {
            greatGrandFather = nullptr;
        }
    } while (father != nullptr);
    return 1;

}

template<typename D>
int AVLTree<D>::removeElement (const D &data) {
    if (!root)
        return 0;
    AVLNode *current = root;
    AVLNode *father = nullptr;
    AVLNode *grandFather = nullptr;
    stack<AVLNode *> routes;
    while (current) {
        if (data > current->data) {
            father = current;
            current = current->rightNode;
        } else if (data < current->data) {
            father = current;
            current = current->leftNode;
        } else {
            break;
        }
    }
    if (current == nullptr)
        return 0;
    //Found
    auto copier = current;
    if (current->leftNode) {
        routes.push(current);
        father = current;
        current = father->leftNode;
        while (current->rightNode) {
            routes.push(current);
            father = current;
            current = father->rightNode;
        }
        copier->data = current->data;
        father->rightNode = current->leftNode;
    } else if (current->rightNode) {
        routes.push(current);
        father = current;
        current = father->rightNode;
        while (current->leftNode) {
            routes.push(current);
            father = current;
            current = father->leftNode;
        }
        copier->data = current->data;
        father->leftNode = current->rightNode;
    } else if (father) {
        if (father->leftNode == current)
            father->leftNode = nullptr;
        else
            father->rightNode = nullptr;
    }
//    routes.pop();
    if (!father) {
        root = nullptr; //Just one node in the tree
        current = father;
    }
    if (!routes.empty()) {
        father = routes.top();
        routes.pop();
    } else father = nullptr;
    if (!routes.empty()) {
        grandFather = routes.top();
        routes.pop();
    }
    while (father) {
        int height = getHeight(father);
        if (getHeight(father->rightNode) - getHeight(father->leftNode) > 1) { //Current is leftChild of father, L rotate
            if (getHeight(father->rightNode->rightNode) - getHeight(father->rightNode->leftNode) > 0) {
                if (grandFather && father == grandFather->leftNode) {
                    grandFather->leftNode = father = father->LRotate();
                } else if (grandFather && father == grandFather->rightNode) {
                    grandFather->rightNode = father = father->LRotate();
                } else {
                    father = father->LRotate();
                }
            } else {
                if (grandFather && father == grandFather->leftNode) {
                    grandFather->leftNode = father = father->RLRotate();
                } else if (grandFather && father == grandFather->rightNode) {
                    grandFather->rightNode = father = father->RLRotate();
                } else {
                    father = father->RLRotate();
                }
            }
        } else if (getHeight(father->rightNode) - getHeight(father->leftNode) < -1) {
            if (getHeight(father->leftNode->rightNode) - getHeight(father->leftNode->leftNode) > 0) {
                if (grandFather && father == grandFather->leftNode) {
                    grandFather->leftNode = father = father->LRRotate();
                } else if (grandFather && father == grandFather->rightNode) {
                    grandFather->rightNode = father = father->LRRotate();
                } else {
                    father = father->LRRotate();
                }
            } else {
                if (grandFather && father == grandFather->leftNode) {
                    grandFather->leftNode = father = father->RRotate();
                } else if (grandFather && father == grandFather->rightNode) {
                    grandFather->rightNode = father = father->RRotate();
                } else {
                    father = father->RRotate();
                }
            }
        } else {
            //Do Nothing
        }
        if (getHeight(father) == height)
            return 1;
        else if (!routes.empty()) {
            current = father;
            father = grandFather;
            grandFather = routes.top();
            routes.pop();
        } else
            return 1;
    }
    return 1;
}

#endif //DATASTRUCTURE_AVLTREE_H
