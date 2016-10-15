//
// Created by claim on 16-10-15.
//

#include <iostream>
#include "stack.h"

class systemConverter {
    const int mode;
    int source;
    bool underZero;
    linkedStack<char> result;
public:
    systemConverter (int mode = 10);

    systemConverter &getSource (int source);

    void putResult ();
};

systemConverter::systemConverter (int mode) : mode(mode), underZero(false) {}

systemConverter &systemConverter::getSource (int source) {
    this->source = abs(source);
    if (source < 0) {
        underZero = true;
    }
    int temp;
    while (this->source) {
        temp = this->source % mode;
        result.push((char) temp + '0');
        this->source /= mode;
    }
    result.push(0);
    return *this;
}

void systemConverter::putResult () {
    if (underZero)
        cout << '-';
    while (!result.empty()) {
        cout << result.top();
        result.pop();
    }
    cout << endl;
    underZero = false;
}

int main () {
    systemConverter toEight(8);
    systemConverter toFive(5);
    toEight.getSource(-98).putResult();
    toEight.getSource(80).putResult();
    toFive.getSource(50).putResult();
}