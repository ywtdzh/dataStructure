//
// Created by claim on 16-10-22.
//

#include "caller.h"
#include <ctime>

int main () {
    caller bank;
    srand((unsigned int) time(NULL));
    for (int i = 0; i < 20; ++i) {
        int type = rand() % 7 + 1; //From 1 to 7
        bank.getUser(rand() % 4 + 1, type < 6 ? user::NORMAL
                                              : (type < 7 ? user::VIP : user::PUBLIC));
        putchar('\n');
        bank.printList();
        putchar('\n');
        bank.tick();
    }
    while (!bank.isEmpty()) {
        putchar('\n');
        bank.printList();
        putchar('\n');
        bank.tick();
    }
    return 0;
}