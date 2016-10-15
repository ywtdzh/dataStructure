//
// Created by claim on 16-10-15.
//
#include "calculator.h"

int main (int argn, char *argv[]) {
    calculator cal;
    cal.readLine("3.1+2*9^(1+2)#");
    cout << cal.calculate() << endl;
}
