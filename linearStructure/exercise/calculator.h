//
// Created by claim on 16-10-15.
//

#ifndef DATASTRUCTURE_CALCULATOR_H
#define DATASTRUCTURE_CALCULATOR_H

#include "stack.h"
#include <string>
#include <iostream>

using namespace std;

class calculator {
    enum {
        IN = 0, OUT = 1
    };
    linkedStack<double> operands;
    linkedStack<char> operators;
    string source;

    const int getOp (char *, stringstream &sOut);

    const double calTwoOperand (char _operator, double op1, double op2);

    const int priority (const char &op, bool mode) const;

public:
    calculator ();

    void readLine (string source = "");

    const double calculate ();

    const calculator &operator= (const calculator &)= delete;

    calculator (const calculator &) = delete;
};


#endif //DATASTRUCTURE_CALCULATOR_H
