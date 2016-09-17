#ifndef DATASTRUCTURE_SQ_LIST_H
#define DATASTRUCTURE_SQ_LIST_H

#include <limits>
#include "data.h"
#define LIST_SIZE 15
#define ERRORCODE -2147483648


enum {
    UNORDERED = 0,
    ORDERED = 1,
};

class sqList {
    bool mode;
    int length;
    data content[LIST_SIZE];
public:
    data *getElement(int position);

    data getOutMin();

    sqList(int mode = UNORDERED);

    void addElement(data value);

    void removeAllByValue(data value);

    void removeByInterval(data min, data max);

    void printList();
};

#endif //DATASTRUCTURE_SQ_LIST_H