//
// Created by claim on 16-10-29.
//

#include <iostream>
#include "KMPAlgorithm.h"

int KMPPattern::getK (int position) {
    string source = stringPattern.substr(0, (unsigned long) position + 1);
    int k = 0;
    for (int i = 1; i < source.length(); ++i) {
        if (source.substr(0, (unsigned long) i) ==
            source.substr(source.length() - i, (unsigned long) i)) {
            k = i;
        }
    }
    return k;
}

KMPPattern::KMPPattern (string input) {
    if (input != "") {
        stringPattern = input;
    } else {
        cin >> stringPattern;
    }
    init();
}

void KMPPattern::init () {
    int length = (int) stringPattern.length();
    next.clear();
    for (int i = 0; i < length; ++i) {
        next.push_back(i + 1 - getK(i));
    }
}

void KMPPattern::input (string source) {
    if (source != "") {
        stringPattern = source;
    } else {
        cin >> stringPattern;
    }
    init();
}

int KMPPattern::match (string target) {
    unsigned long length = stringPattern.length();
    unsigned long max = target.length();
    if (target.length() < length)
        return -1;
    unsigned long position = 0;
    while (position + length <= max) {
        if (target.substr(position, length) == stringPattern)
            return (int) position;
        else {
            int temp;
            for (int i = 0; i < max; ++i) {
                if (stringPattern[i] != target[position]) {
                    temp = i;
                    break;
                }
            }
            //KMP:
            position += next[temp];
            //Burst Force:
//          position++;
        }

    }
    return -1;
}
