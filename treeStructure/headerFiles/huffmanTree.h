//
// Created by claim on 16-11-28.
//

#ifndef DATASTRUCTURE_HUFFMANTREE_H
#define DATASTRUCTURE_HUFFMANTREE_H

#include <memory>
#include <vector>
#include <stack>
#include <algorithm>


using namespace std;

template<typename D>
class huffmanTree {
    struct huffmanNode;
    vector<huffmanNode *> heap;
    huffmanNode *root;
    const D noData;
    bool completed;
    struct result {
        D data;
        vector<bool> encoding;
    };

    struct huffmanNode {
        double weight;
        D data;

        huffmanNode *leftNode, *rightNode;

        huffmanNode (double weight, D data) : weight(weight), data(data), leftNode(nullptr), rightNode(nullptr) {};

        bool haveData () { return data != noData; }

        void getResults (vector<bool> currentCode, vector<result> *res) {
            if (leftNode) {
                {
                    auto temp = currentCode;
                    temp.push_back(false);
                    leftNode->getResults(temp, res);
                }
                {
                    //Must have rightNode
                    auto temp = currentCode;
                    temp.push_back(true);
                    rightNode->getResults(temp, res);
                }
            } else {
                result temp;
                temp.data = data;
                temp.encoding = currentCode;
                res->push_back(temp);
            }

        }

        static bool greaterThan (huffmanNode *a, huffmanNode *b) {
            return a->weight > b->weight;
        }
    };

    void recycleHandler (huffmanNode *root) {
        if (root->leftNode) {
            recycleHandler(root->leftNode);
            recycleHandler(root->rightNode);
        }
        delete root;
    }

public:
    huffmanTree (D noData) : root(nullptr), noData(noData), completed(false) {}

    int addElement (double weight, D data) {
        if (!completed) {
            heap.push_back(new huffmanNode(weight, data));
            return 1;
        } else
            return 0;
    }

    void generateTree () {
        auto greaterThan = huffmanNode::greaterThan;
        make_heap(heap.begin(), heap.end(), greaterThan);
        while (heap.size() > 1) {
            huffmanNode *temp = new huffmanNode(0, noData);
            temp->leftNode = heap[0];
            pop_heap(heap.begin(), heap.end(), greaterThan);
            heap.pop_back();
            temp->rightNode = heap[0];
            pop_heap(heap.begin(), heap.end(), greaterThan);
            heap.pop_back();
            temp->weight = temp->leftNode->weight + temp->rightNode->weight;
            heap.push_back(temp);
            push_heap(heap.begin(), heap.end(), greaterThan);
        }
        root = heap[0];
        completed = true;
    }

    vector<result> getEncoding () {
        vector<bool> coding;
        vector<result> res;
        root->getResults(coding, &res);
        return res;
    }

    ~huffmanTree () {
        recycleHandler(root);
    }
};


#endif //DATASTRUCTURE_HUFFMANTREE_H
