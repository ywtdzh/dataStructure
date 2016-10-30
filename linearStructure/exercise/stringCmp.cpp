//
// Created by claim on 16-10-30.
//
#include <string>
#include <cassert>

using namespace std;

int strcmp (string &&first, string &&last) {
    unsigned long firstLength = first.length();
    unsigned long lastLength = last.length();
    unsigned long minLength = firstLength > lastLength ? lastLength : firstLength;
    for (int i = 0; i < minLength; ++i) {
        if (first[i] > last[i])
            return 1;
        else if (first[i] < last[i])
            return -1;
    }
    if (firstLength > lastLength)
        return 1;
    else if (firstLength < lastLength)
        return -1;
    else
        return 0;
}

