//
// Created by claim on 16-12-13.
//

#include "MatrixGraph.h"

int main () {
    MatrixGraph<int> graph;
    MatrixGraph<int> graphWithoutDirection;
    graph.addElement(0);
    graph.addElement(1);
    graph.addElement(2);
    graph.addElement(3);
    graph.addElement(4);
    graphWithoutDirection.addElement(0);
    graphWithoutDirection.addElement(1);
    graphWithoutDirection.addElement(2);
    graphWithoutDirection.addElement(3);
    graphWithoutDirection.addElement(4);
    graph.connect(0, 1, 7);
    graph.connect(0, 3, 8);
    graph.connect(1, 3, 4);
    graph.connect(1, 2, 6);
    graph.connect(3, 4, 3);
    graph.connect(4, 2, 9);
    graph.connect(2, 0, 2);
    graphWithoutDirection.connectNoDirection(0, 1, 7);
    graphWithoutDirection.connectNoDirection(0, 3, 8);
    graphWithoutDirection.connectNoDirection(1, 3, 4);
    graphWithoutDirection.connectNoDirection(1, 2, 6);
    graphWithoutDirection.connectNoDirection(3, 4, 3);
    graphWithoutDirection.connectNoDirection(4, 2, 9);
    graphWithoutDirection.connectNoDirection(2, 0, 2);

    auto result = graph.getDijkstraLength(0);
    auto result2 = graph.getFloydMatrix();
//    auto loop = graph.getLoop();
    auto tree = graphWithoutDirection.getGeneratedTree();
    return 0;
}