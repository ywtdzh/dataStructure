//
// Created by claim on 16-12-11.
//

#ifndef DATASTRUCTURE_BASICGRAPH_H
#define DATASTRUCTURE_BASICGRAPH_H

#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

template<typename D>
class BasicGraph {
    struct edge;

    struct node {
        D data;
        edge *firstEdge;

        void addEdge (edge *target) {
            if (!firstEdge) {
                firstEdge = target;
            } else {
                edge *iter = firstEdge;
                while (iter->next)iter = iter->next;
                iter->next = target;
                iter->next->next = nullptr;
            }
        }

        bool operator== (const node &target) const { return data == target.data; }

        bool operator< (const node &target) const { return data < target.data; }

        bool operator> (const node &target) const { return data > target.data; }

        node (D data) : data(data) { firstEdge = nullptr; }
    };

    struct edge {
        int first, second;
        double weight;
        edge *next;

        edge (int first, int second, double weight) : first(first), second(second),
                                                      weight(weight) { next = nullptr; }
    };


    vector<node> nodes;

    int connectHandler (int firstIndex, int secondIndex, double weight);

    void DMS_PrintHandler (int index, vector<bool> &visited);

public:
    struct treeNode {
        D data;
        vector<treeNode *> children;

        treeNode (D data) : data(data) {}
    };

    BasicGraph () {}

    void addNode (D data);

    int connect (int firstIndex, int secondIndex, double weight = 1);

    void DMS_Print ();

    void BFS_Print ();

    treeNode *PrimGenerateTree ();

    treeNode *KruskalGenerateTree ();
};

template<typename D>
typename BasicGraph<D>::treeNode *BasicGraph<D>::KruskalGenerateTree () {
    vector<edge *> edges;
    vector<edge *> effective;
    vector<set<node>> connected;
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i].firstEdge) {
            auto current = nodes[i].firstEdge;
            edges.push_back(current);
            while (current->next) {
                current = current->next;
                edges.push_back(current);
            }
        }
        ///////////////////////////////////////////////
        set<node> temp;
        temp.insert(nodes[i]);
        connected.push_back(temp);
    }
    while (!edges.empty()) {
        edge *min = edges[0];
        if (edges.size() == 1)
            edges.erase(edges.begin());
        for (int j = 0; j < edges.size(); ++j) {
            if (edges[j]->weight < min->weight) {
                min = edges[j];
                edges.erase(edges.begin() + j);
                break;
            } else if (j = edges.size() - 1) {
                edges.erase(edges.begin());
            }
        }
        //Minimum edge gotten
        for (int i = 0; i < connected.size(); ++i) {
            if (find(connected[i].begin(), connected[i].end(), node(min->first)) != connected[i].end() &&
                find(connected[i].begin(), connected[i].end(), node(min->second)) == connected[i].end()) {
                effective.push_back(min);
                for (int j = 0; j < connected.size(); ++j) {
                    if (find(connected[i].begin(), connected[i].end(), node(min->second)) != connected[i].end()) {
                        //Union
                        connected[i].insert(connected[j].begin(), connected[j].end());
                        connected.erase(connected.begin() + j);
                        break;
                    }
                }
            }
        }
    }
    for (int k = 0; k < effective.size(); ++k) {
        for (int i = k + 1; i < effective.size(); ++i) {
            if (effective[k]->first == effective[i]->second && effective[k]->second == effective[i]->first) {
                if (effective[k]->first < effective[k]->second)
                    effective.erase(effective.begin() + i);
                else
                    effective.erase(effective.begin() + k);
            }
            //去重
        }
    }
    treeNode *root = new treeNode(effective[0]->first);
    root->children.push_back(new treeNode(effective[0]->second));
    effective.erase(effective.begin());
    while (!effective.empty()) {
        queue<treeNode *> routes;
        routes.push(root);
        for (int i = 0; i < effective.size(); ++i) {
            while (!routes.empty()) {
                if (routes.front()->data == effective[i]->first) {
                    routes.front()->children.push_back(new treeNode(effective[i]->second));
                    effective.erase(effective.begin() + i);
                    break;
                } else {
                    for (int j = 0; j < routes.front()->children.size(); ++j) {
                        routes.push(routes.front()->children[j]);
                    }
                }
                routes.pop();
            }
        }
    }
    return root;
}

template<typename D>
typename BasicGraph<D>::treeNode *BasicGraph<D>::PrimGenerateTree () {
    vector<bool> U;  //顶点集
    vector<edge *> TE; //边集
    for (int i = 0; i < nodes.size(); ++i) {
        U.push_back(false);
    }
    U[0] = true;
    treeNode *root = nullptr;
    for (int j = 0; j < nodes.size() - 1; ++j) {
        for (int i = 0; i < nodes.size(); ++i) {
            edge *iter = nodes[i].firstEdge;
            edge *target = nullptr;
            if (find(TE.begin(), TE.end(), iter) == TE.end() &&
                (U[iter->first] && !U[iter->second] || U[iter->second] && !U[iter->first])) {
                target = iter;
            }
            while (iter->next) {
                iter = iter->next;
                if (!target) {
                    if (find(TE.begin(), TE.end(), iter) == TE.end() &&
                        (U[iter->first] && !U[iter->second] || U[iter->second] && !U[iter->first])) {
                        target = iter;
                    }
                } else {
                    if (find(TE.begin(), TE.end(), iter) == TE.end() && target->weight > iter->weight &&
                        (U[iter->first] && !U[iter->second] || U[iter->second] && !U[iter->first])) {
                        target = iter;
                    }
                }
            }
            if (target) {
                TE.push_back(target);
                if (U[target->first]) {
                    U[target->second] = true;
                } else {
                    U[target->first] = true;
                }
            }
        }
    }
    for (int k = 0; k < TE.size(); ++k) {
        int first = TE[k]->first < TE[k]->second ? TE[k]->first : TE[k]->second;
        int second = TE[k]->second < TE[k]->first ? TE[k]->first : TE[k]->second;
        if (!root) {
            root = new treeNode(nodes[first].data);
            root->children.push_back(new treeNode(nodes[second].data));
        } else {
            //treeNode *current;
            queue<treeNode *> routes;
            routes.push(root);
            while (!routes.empty() && routes.front()->data != nodes[first].data) {
                for (int i = 0; i < routes.front()->children.size(); ++i) {
                    routes.push(routes.front()->children[i]);
                }
                routes.pop();
            }
            if (!routes.empty()) {
                treeNode *iter = routes.front();
                iter->children.push_back(new treeNode(nodes[second].data));
            }
        }
    }
    return root;
}

template<typename D>
void BasicGraph<D>::BFS_Print () {
    queue<int> routes;
    vector<bool> visited;
    for (int i = 0; i < nodes.size(); ++i) {
        visited.push_back(false);
    }
    int current;
    for (int j = 0; j < nodes.size(); ++j) {
        routes.push(j);
        while (!routes.empty()) {
            current = routes.front();
            routes.pop();
            if (!visited[current]) {
                cout << nodes[current].data << endl;
                visited[current] = true;
                if (nodes[current].firstEdge) {
                    edge *iter = nodes[current].firstEdge;
                    routes.push(iter->second == current ? iter->first : iter->second);
                    while (iter->next) {
                        iter = iter->next;
                        routes.push(iter->second == current ? iter->first : iter->second);
                    }
                }
            }

        }
    }

}

template<typename D>
void BasicGraph<D>::DMS_PrintHandler (int index, vector<bool> &visited) {
    if (!visited[index]) {
        cout << nodes[index].data << endl;
        visited[index] = true;
        if (nodes[index].firstEdge) {
            int count = 0;
            edge *iter = nodes[index].firstEdge;
            DMS_PrintHandler(iter->second == index ? iter->first : iter->second, visited);
            while (iter->next) {
                iter = iter->next;
                DMS_PrintHandler(iter->second == index ? iter->first : iter->second, visited);
            }
        }

    }
}

template<typename D>
void BasicGraph<D>::addNode (D data) {
    nodes.push_back(node(data));
}

template<typename D>
int BasicGraph<D>::connectHandler (int firstIndex, int secondIndex, double weight) {
    if (firstIndex < 0 || secondIndex >= nodes.size())
        return 0;
    if (!nodes[firstIndex].firstEdge) {
        nodes[firstIndex].firstEdge = new edge(firstIndex, secondIndex, weight);
        return 1;
    } else {
        edge *iter = nodes[firstIndex].firstEdge;
        while (iter->next) {
            if (iter->first == firstIndex && iter->second == secondIndex
                || iter->first == secondIndex && iter->second == firstIndex)
                return 0;
            iter = iter->next;
        }
        if (iter->first == firstIndex && iter->second == secondIndex
            || iter->first == secondIndex && iter->second == firstIndex)
            return 0;
        iter->next = new edge(firstIndex, secondIndex, weight);
        return 1;
    }
}

template<typename D>
int BasicGraph<D>::connect (int firstIndex, int secondIndex, double weight) {
    return
            connectHandler(firstIndex, secondIndex, weight) &&
            connectHandler(secondIndex, firstIndex, weight);
}

template<typename D>
void BasicGraph<D>::DMS_Print () {
    vector<bool> visited;
    for (int i = 0; i < nodes.size(); ++i) {
        visited.push_back(false);
    }
    for (int j = 0; j < nodes.size(); ++j) {
        DMS_PrintHandler(j, visited);
    }
}


#endif //DATASTRUCTURE_BASICGRAPH_H
