//
// Created by claim on 16-10-30.
//

#ifndef DATASTRUCTURE_TEXTFIELD_H
#define DATASTRUCTURE_TEXTFIELD_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class TextField {
    string content;
    int cursor;
public:
    TextField (const string &content);

    void input (const string &content);

    const int getCursor () const;

    void printText () const;

    void moveCursor (const int position);

    void appendText (const string &source);

    void insertText (const string &source);

    const unsigned long getLength () const;

    void overWrite (const string &source);

    const int findText (const string &target) const;

    void backspace ();

    const unsigned long count (const char ch) const;

    const string getContent () const;
};


#endif //DATASTRUCTURE_TEXTFIELD_H
