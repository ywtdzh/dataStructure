//
// Created by claim on 16-10-15.
//

#include <sstream>
#include "calculator.h"
#include "cmath"

calculator::calculator () {
    operators.push('#');
}

const int calculator::getOp (char *current, stringstream &sOut) {
    if (sOut.peek() == '+' || sOut.peek() == '-' || sOut.peek() == '*' || sOut.peek() == '/' || sOut.peek() == '^'
        || sOut.peek() == '#' || sOut.peek() == '(' || sOut.peek() == ')') {
        sOut >> current[0];
        return 1;
    } else if (sOut.peek() <= '9' && sOut.peek() >= '0' || sOut.peek() == '.') {
        for (int i = 0; 1; ++i) {
            if ((sOut.peek() >= '0' && sOut.peek() <= '9') || sOut.peek() == '.') {
                if (i < 19) {
                    sOut >> current[i];
                }
            } else {
                current[i] = 0;
                break;
            }
        }
        return 0;
    } else {
        return 2;
    }
}

void calculator::readLine (string source) {
    if (source == "") {
        cin >> this->source;
    } else {
        this->source = source;
    }
}

const double calculator::calTwoOperand (char _operator, double op1, double op2) {
    switch (_operator) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
        case '^':
            return pow(op1, op2);
        default:
            return -1;
    }
}

const int calculator::priority (const char &op, bool mode) const {
    if (mode == IN)
        switch (op) {
            case '#':
                return 0;
            case '(':
                return 1;
            case '^':
                return 7;
            case '*':
            case '/':
                return 5;
            case '+':
            case '-':
                return 3;
            case ')':
                return 8;
            default:
                return -1;
        }
    else //mode == OUT
        switch (op) {
            case '#':
                return 0;
            case '(':
                return 8;
            case '^':
                return 6;
            case '*':
            case '/':
                return 4;
            case '+':
            case '-':
                return 2;
            case ')':
                return 1;
            default:
                return -1;
        }
}

const double calculator::calculate () {
    stringstream sOut(source);
    char current[20];
    while (!sOut.eof()) {
        int status = getOp(current, sOut); //Operator == 1, operand == 0, quit == 2
        if (status == 1) { //operator gotten
            char opOut = current[0];
            char opIn = operators.top();
            while (priority(opIn, IN) > priority(opOut, OUT)) {
                operators.pop();
                double opD1, opD2;
                try {
                    operands.pop(&opD2);
                    operands.pop(&opD1);
                } catch (exception e) {
                    cout << "输入不合法" << endl;
                    exit(1);
                }
                operands.push(calTwoOperand(opIn, opD1, opD2));
                opIn = operators.top();
            }
            if (priority(opIn, IN) < priority(opOut, OUT)) {
                operators.push(opOut);
            } else { //priority(opIn, IN) = priority(opOut, OUT)
                operators.pop();
            }
        } else if (status == 0) { //operand gotten
            double temp;
            stringstream(current) >> temp;
            operands.push(temp);
        }
    }
    try {
        double result;
        operands.pop(&result);
        operators.push('#');
        return result;
    } catch (exception e) {
        cout << "输入不合法" << endl;
        exit(1);
    }
}