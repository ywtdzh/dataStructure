//
// Created by claim on 16-10-15.
//
#include "calculator.h"

int main (int argn, char *argv[]) {
    calculator cal;
    cal.readLine("3.1+2*9^(1+2)#"); //should be 1461.1
    cout << cal.calculate() << endl;
    cal.readLine("3.1+2.9*10+2^1#"); //should be 34.1
    cout << cal.calculate() << endl;
}
