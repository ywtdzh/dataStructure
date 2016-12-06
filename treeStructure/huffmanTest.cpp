//
// Created by claim on 16-11-28.
//

#include "huffmanTree.h"
#include <fstream>

int main () {
    huffmanTree<char> coder(-2);
    ifstream fin("data.dat");
    vector<char> fileContent;
    if (fin.is_open()) {
        while (!fin.eof()) {
            fileContent.push_back((char) (fin.get()));
        }
    }
    struct element {
        char data;
        double weight;
    };
    vector<element> elements;
    for (auto data = fileContent.begin(); data < fileContent.end(); data++) {
        bool exist = 0;
        for (auto iter = elements.begin(); iter < elements.end(); iter++) {
            if (*data == (*iter).data) {
                exist = 1;
                (*iter).weight++;
                break;
            }
        }
        if (!exist) {
            element temp;
            temp.weight = 1;
            temp.data = *data;
            elements.push_back(temp);
        }
    }
    for (auto iter = elements.begin(); iter < elements.end(); iter++) {
        coder.addElement((*iter).weight, (*iter).data);
    }
    coder.generateTree();
    auto results = coder.getEncoding();
    ofstream fOut("output.dat", ios::binary);
    for (auto character = fileContent.begin(); character < fileContent.end(); character++) {
        for (auto result = results.begin(); result < results.end(); result++) {
            if ((*result).data == *character)
                for (auto iter = (*result).encoding.begin(); iter < (*result).encoding.end(); iter++) {
                    fOut << *iter;
                }
        }
    }
    fOut.close();
    return 0;
}