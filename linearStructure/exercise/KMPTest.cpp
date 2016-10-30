//
// Created by claim on 16-10-30.
//
#include <KMPAlgorithm.h>
#include <cassert>

int main () {
    KMPPattern pattern("cococola");
    assert(pattern.match("coco") == -1);
    assert(pattern.match("cococolaCorporition") == 0);
    assert(pattern.match("ilovecococolaCorporition") == 5);
    assert(pattern.match("ilovecocacolaCorporition") == -1);
    KMPPattern patternXVI("abcaabbcabcaabdab");
    assert(patternXVI.match("coco") == -1);
    return 0;
}