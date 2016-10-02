//
// Created by claim on 16-9-12.
//

#include <iostream>
#include <cassert>
#include "stack.h"

using namespace std;

int main() {
    //ordered stack test
    int temp;
    orderStack<int> oStack;
    assert(oStack.empty());
    oStack.push(8);
    cout << oStack.top() << " should be 8" << endl;
    oStack.pop(&temp);
    assert(oStack.empty());
    cout << temp << " should be 8" << endl;
    oStack.push(7);
    oStack.push(2);
    oStack.push(5);
    cout << oStack.top() << " should be 5" << endl;
    oStack.pop(&temp);
    cout << oStack.top() << " should be 2," << temp << " should be 5" << endl;
    //linked stack test
    linkedStack<int> lStack;
    assert(lStack.empty());
    lStack.push(8);
    cout << lStack.top() << " should be 8" << endl;
    lStack.pop(&temp);
    assert(lStack.empty());
    cout << temp << " should be 8" << endl;
    lStack.push(7);
    lStack.push(2);
    lStack.push(5);
    cout << lStack.top() << " should be 5" << endl;
    lStack.pop(&temp);
    cout << lStack.top() << " should be 2," << temp << " should be 5" << endl;
}