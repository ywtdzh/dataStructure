//
// Created by claim on 16-12-13.
//

#ifndef DATASTRUCTURE_MATRIXGRAPH_H
#define DATASTRUCTURE_MATRIXGRAPH_H

#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

template<typename D>
class MatrixGraph {
    vector<D> nodes;
    vector<vector<double>> edges;

    vector<int> getLoopHandler ();

public:
    void addElement (const D &data);

    void connect (int first, int second, double weight) {
        edges[first][second] = weight;
    }

    void connectNoDirection (int first, int second, double weight) {
        edges[first][second] = weight;
        edges[second][first] = weight;
    }

    vector<double> getDijkstraLength (int index);

    vector<vector<double>> getFloydMatrix ();

    vector<int> getLoop ();

    vector<vector<double>> getGeneratedTree ();
};

template<typename D>
void MatrixGraph<D>::addElement (const D &data) {
    nodes.push_back(data);
    for (int i = 0; i < edges.size(); ++i) {
        edges[i].push_back(INFINITY);
    }
    edges.push_back(vector<double>());
    for (int j = 0; j < edges.size(); ++j) {
        edges[edges.size() - 1].push_back(INFINITY);
    }
}

template<typename D>
vector<double> MatrixGraph<D>::getDijkstraLength (int index) {
    vector<bool> gotten;
    for (int i = 0; i < nodes.size(); ++i) {
        gotten.push_back(false);
    }
    vector<double> result;
    for (int j = 0; j < nodes.size(); ++j) {
        result.push_back(INFINITY);
    }
    gotten[index] = true;
    result[index] = 0;
    int inner = INFINITY, outer = INFINITY, minWeight = INFINITY;
    for (int l = 0; l < nodes.size() - 1; ++l) {
        for (int k = 0; k < nodes.size(); ++k) {
            if (gotten[k]) {
                for (int i = 0; i < nodes.size(); ++i) {
                    if (!gotten[i] && result[k] + edges[k][i] < minWeight && k != i) {
                        inner = k;
                        outer = i;
                        minWeight = edges[k][i];
                    }
                }
            }
        }
        result[outer] = result[inner] + edges[inner][outer];
        gotten[outer] = true;
        outer = inner = minWeight = INFINITY;
    }
    return result;

}

template<typename D>
vector<vector<double>> MatrixGraph<D>::getFloydMatrix () {
    vector<vector<double>> result = edges;
    vector<vector<int>> path;
    //Initialize path
    for (int i = 0; i < nodes.size(); ++i) {
        vector<int> temp;
        for (int j = 0; j < nodes.size(); ++j) {
            temp.push_back(INFINITY);
        }
        path.push_back(temp);
    }
    for (int l = 0; l < nodes.size(); ++l) {
        for (int i = 0; i < nodes.size(); ++i) {
            if (edges[i][l] < INFINITY)
                path[i][l] = i;
        }
    }
    for (int k = 0; k < nodes.size(); ++k) {
        for (int i = 0; i < nodes.size(); ++i) {
            for (int j = 0; j < nodes.size(); ++j) {
                if (result[i][j] > result[i][k] + result[k][j] && result[i][k] != INFINITY &&
                    result[k][j] != INFINITY) {
                    path[i][j] = k;
                    result[i][j] = result[i][k] + result[k][j];
                }
            }
        }
    }
    return result;
}

template<typename D>
vector<int> MatrixGraph<D>::getLoopHandler () {
    //Dangerous private method, may destroy Graph. Make sure to call this function by a temporary graph object
    vector<int> result;
    vector<int> loopElement;
    for (int k = 0; k < edges.size(); ++k) {
        loopElement.push_back(k);
    }
    for (int p = 0; p < edges.size(); p++) {
        bool hasLoop = true;
        for (int i = 0; i < edges.size(); ++i) {
            bool noEntry = true;
            for (int j = 0; j < edges.size(); ++j) {
                if (edges[j][i] != INFINITY) {
                    noEntry = false;
                    break;
                }
            }
            if (noEntry) {
                for (int j = 0; j < edges.size(); ++j) {
                    edges[j].erase(edges[j].begin() + i);
                }
                edges.erase(edges.begin() + i);
                loopElement.erase(loopElement.begin() + i);
                hasLoop = false;
                break;
            }
        }
        if (hasLoop && edges.size() > 1) {
            for (int i = 0; i < edges.size(); ++i) {
                bool noExit = true;
                for (int j = 0; j < edges.size(); ++j) {
                    if (edges[i][j] != INFINITY) {
                        noExit = false;
                        break;
                    }
                }
                if (noExit) {
                    for (int j = 0; j < edges.size(); ++j) {
                        edges[j].erase(edges[j].begin() + i);
                    }
                    edges.erase(edges.begin() + i);
                    loopElement.erase(loopElement.begin() + i);
                    break;
                }
            }
        }
    }
    int index = 0, base = 0;
    while (1) {
        index = base;
        result.push_back(loopElement[index]);
        for (int l = base; l < loopElement.size(); ++l) {
            if (edges[index][l] != INFINITY && (find(result.begin(), result.end(), l) == result.end() || l == base)) {
                index = l;
                if (result.size() < 2)
                    l = base;
                else
                    l = base - 1;
                //When next for-loop,l was initialized to base
                result.push_back(loopElement[index]);
                auto iter = find(result.begin(), result.end() - 1, index);
                if (iter != result.end() - 1 && result.size() > 2) {
                    while (iter != result.begin()) {
                        result.erase(iter - 1);
                    }
                    return result;
                }
            }
        }
        result.clear();
        base++;
        if (base > loopElement.size())
            return result;
    }
}

template<typename D>
vector<int> MatrixGraph<D>::getLoop () {
    MatrixGraph<D> temp(*this);
    return temp.getLoopHandler();
}

template<typename D>
vector<vector<double>> MatrixGraph<D>::getGeneratedTree () {
    MatrixGraph<D> temp(*this);
    vector<vector<double>> result = temp.edges;
    vector<int> loop = temp.getLoopHandler();
    while (loop.size() > 2) {
        temp.edges[loop[0]][loop[1]] = INFINITY;
        result[loop[0]][loop[1]] = INFINITY;
        temp.edges[loop[1]][loop[0]] = INFINITY;
        result[loop[1]][loop[0]] = INFINITY;
        loop = temp.getLoopHandler();
    }
    return result;
}

#endif //DATASTRUCTURE_MATRIXGRAPH_H
