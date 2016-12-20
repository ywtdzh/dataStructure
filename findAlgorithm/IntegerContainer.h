//
// Created by claim on 16-12-20.
//

#ifndef DATASTRUCTURE_NINTHTEST_H
#define DATASTRUCTURE_NINTHTEST_H

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::make_shared;

class IntegerContainer {
    struct container {
        vector<int> content;
        shared_ptr<container> next;

        container () : next(nullptr) {}

        void addNext () {
            if (content.size() == 5)
                next = make_shared<container>();
        }
    };

    shared_ptr<container> head;
    shared_ptr<container> tail;

public:
    struct result {
        int index;
        vector<int> *content;

        result (int index, vector<int> *content) : index(index), content(content) {}
    };

    IntegerContainer () {
        head = tail = make_shared<container>();
    }

    void addElement (int ele) {
        if (tail->content.size() == 5) {
            tail->addNext();
            tail = tail->next;
        }
        tail->content.push_back(ele);
    }

    void addElements (const vector<int> elements) {
        for (int i = 0; i < elements.size(); ++i) {
            addElement(elements[i]);
        }
    }

    result search (int target) {
        auto iter = head;
        do {
            for (int i = 0; i < iter->content.size(); ++i) {
                if (target == iter->content[i])
                    return result(i, &(iter->content));
            }
            iter = iter->next;
        } while (iter != nullptr);
        return result(-1, nullptr);
    }
};


#endif //DATASTRUCTURE_NINTHTEST_H
