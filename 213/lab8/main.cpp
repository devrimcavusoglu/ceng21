#include <iostream>
#include <vector>
#include <cstdlib>

#include "Graph.hpp"

using namespace std;

#define VV 10
#define EE 20

void print_decorator() {
    std::cout << "================================================\n";
}

void generateRandomGraph(Graph &G) {
    int edge[EE][2];

    // Building connections (edges) between random nodes.
    int i = 0;
    while (i < EE) {
        edge[i][0] = rand() % G.V();
        edge[i][1] = rand() % G.V();

        if (edge[i][0] == edge[i][1])
            continue;
        else {
            for (int j = 0 ; j < i ; j++) {
                if ((edge[i][0] == edge[j][0] && edge[i][1] == edge[j][1]) ||
                    (edge[i][0] == edge[j][1] && edge[i][1] == edge[j][0]))
                    i--;
            }
        }

        i++;
    }

    // Inserting edges.
    for (int i = 0; i < EE; i++) {
        G.insert(Edge(edge[i][0], edge[i][1]));
    }
}

void test_is_edge(Graph &G) {
    bool e03 = G.isEdge(0, 3);
    bool e13 = G.isEdge(1, 3);

    std::cout << "Edge 0 - 3: " << e03 << std::endl;
    std::cout << "Edge 1 - 3: " << e13 << std::endl;
}

int main() {
    Graph G(VV, false);

    generateRandomGraph(G);

    G.print();
    print_decorator();

    test_is_edge(G);
    print_decorator();

    G.printPath(5);
    print_decorator();
    return 0;
}
