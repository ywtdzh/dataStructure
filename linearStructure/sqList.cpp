//
// Created by claim on 16-9-17.
//
#include <iostream>
#include "sqList.h"

using namespace std;

sqList::sqList(int mode) {
    this->mode = (bool) mode;
    length = 0;
}

data sqList::getOutMin() {
    if (mode == UNORDERED) {
        if (length == 0) {
            cout << "当前顺序表中不存在任何元素!" << endl;
            return ERRORCODE;
        }
        data min = content[0];
        int position = 0;
        for (int i = 0; i < length; ++i) {
            if (content[i] < min) {
                min = content[i];
                position = i;
            }
        }
        content[position] = content[length - 1];
        length--;
        return min;
    } else {
        data min = content[length - 1];
        length--;
        return min;
    }
}

void sqList::removeByInterval(data min, data max) {
    if (mode == UNORDERED) {
        cout << "此顺序表是无序的,不符合题意!" << endl;
        return;
    }
    int minPosition = 0, maxPosition = 0;
    while (content[maxPosition] > max && maxPosition < length)
        maxPosition++;
    if (maxPosition == length) {
        cout << "检索完毕,已删除0个元素" << endl;
        return;
    }
    while (content[minPosition] > min)
        minPosition++;
    const int elementsDeleted = minPosition - maxPosition + 1;
    if (minPosition == length - 1) {

    } else if (elementsDeleted > length - minPosition - 1) {
        for (int endPosition = minPosition + 1, startPosition = maxPosition;
             endPosition < length; ++endPosition, ++startPosition) {
            content[startPosition] = content[endPosition];
        }
    } else {
        for (int i = maxPosition, count = length - elementsDeleted; i < minPosition + 1; ++i, ++count) {
            content[i] = content[count];
        }
    }
    length -= elementsDeleted;
    cout << "检索完毕,已删除" << elementsDeleted << "个元素!" << endl;
}

void sqList::removeAllByValue(data value) {
    if (mode == UNORDERED) {
        int position = 0;
        while (content[position] != value && position < length)
            position++;
        if (position == length) {
            return;
        } else {
            content[position] = content[length - 1];
            length--;
        }
        this->removeAllByValue(value);
    } else {
        cout << "此操作暂时只支持无序顺序表!" << endl;
    }
}

data *sqList::getElement(int position) {
    return &content[position];
}

void sqList::addElement(data value) {
    if (length + 1 > LIST_SIZE) {
        cout << "超过了顺序表最大容量!" << endl;
        return;
    }
    if (mode == UNORDERED) {
        length++;
        content[length - 1] = value;
        return;
    } else {
        int position = length;
        for (int i = 0; i < length; ++i) {
            if (content[i] < value) {
                position = i;
                break;
            }
        }
        for (int j = length; j > position; --j) {
            content[j] = content[j - 1];
        }
        content[position] = value;
        length++;
    }
}

void sqList::printList() {
    for (int i = 0; i < length; ++i) {
        cout<<content[i]<<'\t';
    }
    cout<<endl;
}
