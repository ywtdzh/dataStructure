//
// Created by claim on 16-10-22.
//

#ifndef DATASTRUCTURE_CALLER_H
#define DATASTRUCTURE_CALLER_H

#include "queue.h"

class Window;

class user {
    const int type;
    int needTime;
    int number;

    friend class Window;

    friend class caller;

public:
    enum {
        NORMAL = 0,
        VIP,
        PUBLIC
    };

    user (int time = 1, int type = NORMAL) : type(type), needTime(abs(time)), number(0) {}
};

class Window {
    int type;
    linkedQueue<user> userQueue;

public:
    Window (const int type = user::NORMAL) : type(type) {}

    int getUserNum () { return userQueue.getLength(); }

    void enqueue (user u) {
        userQueue.enQueue(u);
    }

    void tick () {
        if (userQueue.getLength()) {
            const_cast<user &>(userQueue.peek()).needTime--;
            if (!const_cast<user &>(userQueue.peek()).needTime) {
                cout << "Serve complete:User " << const_cast<user &>(userQueue.peek()).number << endl;
                userQueue.deQueue();
            }
        }
    }

    void printList () const {
        linkedQueue<user> temp = userQueue;
        while (temp.getLength()) {
            cout << "User " << temp.peek().number
                 << (temp.peek().type ? (temp.peek().type == 1 ? "\nType:VIP\n" : "\nType:Public\n")
                                      : "\nType:Normal\n");
            temp.deQueue();
        }
    }
};

class caller {
    Window normalWindow[3];
    Window VIPWindow;
    Window publicWindow;
    int number;
public:
    caller () : VIPWindow(user::VIP), publicWindow(user::PUBLIC), number(0) {}

    void tick ();

    void getUser (int time = 1, int type = user::NORMAL);

    void printList ();

    bool isEmpty ();
};


#endif //DATASTRUCTURE_CALLER_H
