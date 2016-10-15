//
// Created by claim on 16-10-15.
//
#include <iostream>
#include <cassert>
#include <sstream>
#include "stack.h"

class checker {
    string source;
    orderStack<char> container;
public:
    checker (int limit = 20);

    void readLine (string source = "");

    bool check ();
};

void checker::readLine (string source) {
    if (source != "") {
        this->source = source;
    } else {
        cin >> source;
    }
}

checker::checker (int limit) : container(limit) {
    container.push('#');
}

bool checker::check () {
    stringstream sOut(source);
    char temp;
    while (!sOut.eof()) {
        sOut >> temp;
        if (temp == '<' || temp == '>' || temp == '(' || temp == ')' || temp == '['
            || temp == ']' || temp == '{' || temp == '}' || temp == '#') {
            switch (temp) {
                case '>':
                    if (container.top() == '<') {
                        container.pop();
                    } else {
                        container.push(temp);
                    }
                    break;
                case ')':
                    if (container.top() == '(') {
                        container.pop();
                    } else {
                        container.push(temp);
                    }
                    break;
                case '}':
                    if (container.top() == '{') {
                        container.pop();
                    } else {
                        container.push(temp);
                    }
                    break;
                case ']':
                    if (container.top() == '[') {
                        container.pop();
                    } else {
                        container.push(temp);
                    }
                    break;
                case '#':
                    if (container.top() == '#') {
                        container.pop();
                    } else {
                        container.push(temp);
                    }
                    break;
                default:
                    container.push(temp);
            }
        }
        temp = 0;
    }
    if (container.empty()) {
        cout << "Check Passed\n";
        container.push('#');
        return true;
    } else {
        cout << "Check Failed\n";
        while (!container.empty()) {
            container.pop();
        }
        container.push('#');
        return false;
    }

}

int main () {
    checker c(40);
    c.readLine("<kofdoi{jfi(os}()90)>asdf #");
    assert(!c.check());
    c.readLine("<kofdoi{jfios}(90)>asdf #");
    assert(c.check());
}