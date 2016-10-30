//
// Created by claim on 16-10-30.
//

#ifndef DATASTRUCTURE_EDITOR_H
#define DATASTRUCTURE_EDITOR_H

#include <vector>
#include "TextField.h"

class Editor {
    vector<TextField> textFields;
    string filename;
    int currentField;
public:
    enum {
        LETTER = 0, NUMBER, PUNCTUATION, WHITE, TOTAL
    };

    Editor (const string &filename);

    bool open (const string &filename);

    bool save () const;

    const string getName () const;

    const int getCursor () const;

    void setCursor (const int position);

    void appendText (const string &source);

    void insertText (const string &source);

    void overWrite (const string &source);

    const int findText (const string &target) const;

    void backspace (int time = 1);

    const int count (int target = TOTAL) const;
};


#endif //DATASTRUCTURE_EDITOR_H