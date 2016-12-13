//
// Created by claim on 16-12-11.
//

#include "BasicGraph.h"

int main () {
    BasicGraph<int> graph;
    graph.addNode(0);
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addNode(5);
    graph.addNode(6);
    graph.addNode(7);
    graph.connect(0, 1, 4);
    graph.connect(0, 2, 2);
    graph.connect(0, 3);
    graph.connect(1, 5, 3);
    graph.connect(3, 6, 5);
    graph.connect(2, 4, 8);
    graph.connect(2, 7, 9);
    graph.DMS_Print();
    putchar('\n');
    graph.BFS_Print();
    putchar('\n');
    auto tree = graph.PrimGenerateTree();
    auto KTree = graph.KruskalGenerateTree();
    return 0;
}