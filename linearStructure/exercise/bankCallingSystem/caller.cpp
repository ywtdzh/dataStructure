//
// Created by claim on 16-10-22.
//

#include "caller.h"

void caller::tick () {
    for (int i = 0; i < 3; ++i) {
        normalWindow[i].tick();
    }
    VIPWindow.tick();
    publicWindow.tick();
}

void caller::getUser (int time, int type) {
    switch (type) {
        case user::NORMAL: {
            int minUserQueue = 0;
            for (int i = 0; i < 3; ++i) {
                if (normalWindow[minUserQueue].getUserNum()
                    > normalWindow[i].getUserNum()) {
                    minUserQueue = i;
                }
            }
            if (normalWindow[minUserQueue].getUserNum()) {
                if (!publicWindow.getUserNum()) {
                    user temp(time, type);
                    temp.number = number;
                    number++;
                    publicWindow.enqueue(temp);
                    break;
                } else if (!VIPWindow.getUserNum()) {
                    user temp(time, type);
                    temp.number = number;
                    number++;
                    VIPWindow.enqueue(temp);
                    break;
                }
            }
            user temp(time, type);
            temp.number = number;
            number++;
            normalWindow[minUserQueue].enqueue(temp);
            break;
        }
        case user::VIP: {
            user temp(time, type);
            temp.number = number;
            number++;
            VIPWindow.enqueue(temp);
            break;
        }
        case user::PUBLIC: {
            user temp(time, type);
            temp.number = number;
            number++;
            publicWindow.enqueue(temp);
            break;
        }
    }
}

void caller::printList () {
    for (int i = 0; i < 3; ++i) {
        if (normalWindow[i].getUserNum()) {
            cout << "Normal Window " << i + 1 << " : \n";
            normalWindow[i].printList();
        }
    }
    if (VIPWindow.getUserNum()) {
        cout << "VIP Window : \n";
        VIPWindow.printList();
    }
    if (publicWindow.getUserNum()) {
        cout << "Public Window : \n";
        publicWindow.printList();
    }
}

bool caller::isEmpty () {
    for (int i = 0; i < 3; ++i) {
        if (normalWindow[i].getUserNum())
            return false;
    }
    if (VIPWindow.getUserNum())
        return false;
    if (publicWindow.getUserNum())
        return false;
    return true;
}