//
// Created by claim on 16-10-30.
//
#include <cassert>
#include <string>

using namespace std;

int strcmp (string &&first, string &&last);

int main () {
    assert(strcmp("iop", "yui") == -1);
    assert(strcmp("yuap", "yui") == -1);
    assert(strcmp("yuip", "yui") == 1);
    assert(strcmp("yuip", "yuip") == 0);
}