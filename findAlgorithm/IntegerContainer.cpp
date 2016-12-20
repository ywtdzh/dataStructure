//
// Created by claim on 16-12-20.
//

#include "IntegerContainer.h"
#include <vector>

using std::vector;

int main () {
    auto container = IntegerContainer();
    int temp[] = {1, 4, 12, 4, 2354, 246, 5, 3, 4, 5, 9, 6, 23, 4, 78, 6, 34, 42, 34, 2, 4, 3, 52, 4, 98, 4, 3, 6, 3,
                  80, 4, 43, 4};
    container.addElements(vector<int>(temp, temp + 33));
    auto result_0 = container.search(23);
    auto result_1 = container.search(22);
    return 0;
}