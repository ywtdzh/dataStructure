//
// Created by claim on 16-10-30.
//

#include <assert.h>
#include "KMPAlgorithm.h"

string reverse (string source) {
    unsigned long length = source.length();
    string result;
    for (int i = 0; i < length; ++i) {
        result.push_back(source[length - i - 1]);
    }
    return result;
}

int matchL (string &&str, string &&subStr) {
    KMPPattern pattern(reverse(subStr));
    int result = pattern.match(reverse(str));
    return (int) (result == -1 ? -1 :
                  (int) str.length() - result - subStr.length());

}

int main () {
    assert(matchL("asd", "aa") == -1);
    assert(matchL("asd", "sd") == 1);
    assert(matchL("asd", "as") == 0);
}