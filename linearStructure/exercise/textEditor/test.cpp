//
// Created by claim on 16-10-30.
//

#include <assert.h>
#include "Editor.h"

int main () {
    Editor textEditor("abc.txt");
    textEditor.appendText("[append]This is a textEditor.\nNow Input here.\n12\n");
    textEditor.backspace(2);
    textEditor.save();
    textEditor.open("abc.txt");
    textEditor.insertText("Header\n");
    textEditor.appendText("\nHello\n");
    textEditor.setCursor(45);
    assert(textEditor.getCursor() == 45);
    textEditor.overWrite("Over\nWritten");
    textEditor.save();
    cout << "find-'append':" << textEditor.findText("append") << endl;
    cout << "count-'letter':" << textEditor.count(Editor::LETTER) << endl;
    cout << "count-'number':" << textEditor.count(Editor::NUMBER) << endl;
    cout << "count-'punctuation':" << textEditor.count(Editor::PUNCTUATION) << endl;
    cout << "count-'white':" << textEditor.count(Editor::WHITE) << endl;
    cout << "count-'total':" << textEditor.count(Editor::TOTAL) << endl;
    system("cat abc.txt");
    return 0;
}