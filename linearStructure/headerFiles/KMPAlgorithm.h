//
// Created by claim on 16-10-29.
//

#ifndef DATASTRUCTURE_KMPALGORITHM_H
#define DATASTRUCTURE_KMPALGORITHM_H

#include <vector>
#include <string>

using namespace std;

class KMPPattern {
    string stringPattern;
    vector<int> next;

    int getK (int position);

    void init ();

public:
    KMPPattern (string input = "");

    void input (string source = "");

    int match (string target);
};


#endif //DATASTRUCTURE_KMPALGORITHM_H
