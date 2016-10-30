//
// Created by claim on 16-10-30.
//

#include "TextField.h"
#include "KMPAlgorithm.h"

TextField::TextField (const string &content) {
    this->content = content;
    cursor = -1;
}

void TextField::input (const string &content) {
    this->content = content;
}

const int TextField::getCursor () const {
    return cursor;
}

void TextField::printText () const {
    cout << content << endl;
}

void TextField::moveCursor (const int position) {
    cursor = position;
}

void TextField::appendText (const string &source) {
    content += source;
    cursor = (int) (content.length() - 1);
}

void TextField::insertText (const string &source) {
    string last = content
            .substr((unsigned long) (cursor + 1), content.length() - cursor - 1);
    string first = content.substr(0, (unsigned long) cursor + 1);
    content = first + source + last;
    cursor = (int) (first.length() + source.length() - 1);
}

const unsigned long TextField::getLength () const {
    return content.length();
}

void TextField::overWrite (const string &source) {
    if (cursor > -1) {
        string last = content.substr((unsigned long) cursor,
                                     content.length() - cursor);
        string first = content.substr(0, (unsigned long) cursor);
        if (source.length() >= last.length()) {
            content = first + source;
            cursor = (int) (content.length() - 1);
        } else {

            content = first + source +
                      last.substr(source.length() + 1);
            cursor = (int) (content.length() - 1);
        }
    } else {
        content = source;
        cursor = (int) (content.length() - 1);
    }
}

const int TextField::findText (const string &target) const {
    KMPPattern pattern(target);
    return pattern.match(content);
}

void TextField::backspace () {
    if (cursor == -1)return;
    string last = content.substr((unsigned long) cursor,
                                 content.length() - cursor - 1);
    string first = content.substr(0, (unsigned long) cursor + 1);
    first.pop_back();
    content = first + last;
    cursor = (int) (content.length() - 1);
}

const unsigned long TextField::count (const char ch) const {
    unsigned long result = 0;
    for (int i = 0; i < content.length(); ++i) {
        if (content[i] == ch)
            result++;
    }
    return result;
}

const string TextField::getContent () const {
    return content;
}
