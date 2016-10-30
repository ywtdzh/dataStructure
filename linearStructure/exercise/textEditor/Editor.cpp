//
// Created by claim on 16-10-30.
//

#include <fstream>
#include "Editor.h"

Editor::Editor (const string &filename) {
    this->filename = filename;
    if (!open(filename)) {
        textFields.push_back(TextField(""));
        currentField = 0;
    }
}

bool Editor::open (const string &filename) {
    char temp = 0;
    string line;
    textFields.clear();
    currentField = 0;
    ifstream fin(filename);
    if (!fin.is_open())
        return false;
    while (fin.good()) {
        temp = fin.get();
        if (temp != '\n')
            line.push_back(temp);
        else {
            textFields.push_back(line);
            line = "";
        }
    }
    if (textFields.empty()) {
        textFields.push_back(TextField(""));
    }
    fin.close();
    return true;
}

bool Editor::save () const {
    ofstream fout(filename);
    if (!fout.is_open())
        return false;
    for (int i = 0; i < textFields.size(); ++i) {
        fout << textFields[i].getContent() << '\n';
    }
    fout.close();
    return true;
}

const string Editor::getName () const {
    return filename;
}

const int Editor::getCursor () const {
    int cursor = 0;
    for (int i = 0; i < currentField; ++i) {
        cursor += textFields[i].getLength() + 1/*\n*/;
    }
    cursor += textFields[currentField].getCursor();
    return cursor;
}

void Editor::setCursor (const int position) {
    int cursor = position;
    for (int i = 0; i < textFields.size(); ++i) {
        if (cursor > textFields[i].getLength()) {
            cursor -= textFields[i].getLength() + 1;
            textFields[i].moveCursor(0);
        } else {
            textFields[i].moveCursor(cursor);
            currentField = i;
            return;
        }
    }
    textFields[textFields.size() - 1]
            .moveCursor((const int) textFields[textFields.size() - 1]
                    .getLength());
    currentField = (int) (textFields.size() - 1);
}

void Editor::appendText (const string &source) {
    currentField = (int) (textFields.size() - 1);
    char temp;
    stringstream sourceString(source);
    string result;
    for (int i = 0; i < source.length(); ++i) {
        temp = (char) sourceString.get();
        if (temp != '\n') {
            result.push_back(temp);
        } else {
            if (result != "") {
                textFields[currentField].appendText(result);
            }
            result.clear();
            textFields.push_back(TextField(""));
            currentField++;
            textFields[currentField]
                    .moveCursor((const int) (textFields[currentField]
                                                     .getLength() - 1));
        }
    }
    if (result != "")
        textFields[currentField].appendText(result);
}

void Editor::insertText (const string &source) {
    char temp;
    stringstream sourceString(source);
    string result;
    for (int i = 0; i < source.length(); ++i) {
        temp = (char) sourceString.get();
        if (temp != '\n') {
            result.push_back(temp);
        } else {
            if (result != "") {
                textFields[currentField].insertText(result);
            }
            result.clear();
            if (currentField + 1 > textFields.size() - 1) {
                textFields.push_back(TextField(""));
                currentField++;
                textFields[currentField]
                        .moveCursor((const int) (textFields[currentField]
                                                         .getLength() - 1));
            } else {
                currentField++;
                textFields.insert(textFields.begin() + currentField,
                                  TextField(textFields[currentField - 1]
                                                    .getContent()
                                                    .substr((unsigned long) i)));
                for (int i = 0; i < textFields[currentField].getLength(); i++) {
                    textFields[currentField - 1].backspace();
                }

                textFields[currentField]
                        .moveCursor(0);
            }
        }
    }
    if (result != "")
        textFields[currentField].insertText(result);
}

void Editor::overWrite (const string &source) {
    char temp;
    stringstream sourceString(source);
    string result;
    for (int i = 0; i < source.length(); ++i) {
        temp = (char) sourceString.get();
        if (temp != '\n') {
            result.push_back(temp);
        } else {
            if (result != "") {
                textFields[currentField].overWrite(result);
            }
            result.clear();
            if (currentField + 1 > textFields.size() - 1) {
                textFields.push_back(TextField(""));
                currentField++;
                textFields[currentField]
                        .moveCursor((const int) (textFields[currentField]
                                                         .getLength() - 1));
            } else {
                currentField++;
                textFields.insert(textFields.begin() + currentField, TextField(""));
                string tempX = textFields[currentField - 1].getContent().substr(0, (unsigned long) (
                        textFields[currentField - 1].getCursor() - 2/*\n+1*/));
                textFields[currentField].moveCursor(0);
                textFields[currentField - 1].moveCursor((const int) (textFields[currentField - 1].getLength() - 1));
                const int length = (const int) textFields[currentField - 1].getLength();
                for (int i = 0; i < length; i++) {
                    textFields[currentField - 1].backspace();
                }
                textFields[currentField - 1].overWrite(tempX);
            }
        }
    }
    if (result != "")
        textFields[currentField].overWrite(result);
}

const int Editor::findText (const string &target) const {
    int result = 0;
    for (int i = 0; i < textFields.size(); ++i) {
        int temp = textFields[i].findText(target);
        if (temp != -1)
            return result + temp;
        else {
            result += textFields[i].getLength() + 1;
        }
    }
    return -1;
}

void Editor::backspace (int time) {
    for (int i = 0; i < time; ++i) {
        textFields[currentField].backspace();
        if (textFields[currentField].getLength() == 0) {
            vector<TextField>::iterator current = textFields.begin() + currentField;
            textFields.erase(current);
            currentField--;
        }
    }
}

const int Editor::count (int target) const {
    int result = 0;
    switch (target) {
        case LETTER:
            for (int i = 0; i < textFields.size(); ++i) {
                for (int j = 0; j < 26; ++j) {
                    result += textFields[i].count((const char) ('a' + j));
                    result += textFields[i].count((const char) ('A' + j));
                }
            }
            break;
        case NUMBER:
            for (int i = 0; i < textFields.size(); ++i) {
                for (int j = 0; j < 10; ++j) {
                    result += textFields[i].count((const char) ('0' + j));
                }
            }
            break;
        case WHITE:
            for (int i = 0; i < textFields.size(); ++i) {
                result += textFields[i].count(' ');
                result++;
            }
            break;
        case TOTAL:
            for (int i = 0; i < textFields.size(); ++i) {
                result += textFields[i].getLength() + 1;
            }
            break;
        case PUNCTUATION:
            result += count(TOTAL) - count(LETTER) - count(NUMBER) - count(WHITE);
            break;
        default:
            result = 0;
    }
    return result;
}
