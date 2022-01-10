#include "Graph.h"
#include "GraphExceptions.h"
#include <iostream>

int main()
{
    Graph g;

    g.InsertVertex("A");
    g.InsertVertex("B");
    g.InsertVertex("C");
    g.InsertVertex("D");
    g.InsertVertex("E");
    g.InsertVertex("F");
    g.InsertVertex("G");
    g.InsertVertex("H");
    g.InsertVertex("I");
    g.InsertVertex("J");


    g.ConnectVertices("A", "B", 1);
    g.ConnectVertices("A", "C", 3);
    g.ConnectVertices("B", "C", 1);
    g.ConnectVertices("B", "D", 2);
    g.ConnectVertices("C", "D", 5);
    g.ConnectVertices("C", "E", 1);
    g.ConnectVertices("D", "E", 3);

    //g.printVertices();
    g.PrintAll();

    std::vector<int> result;
    g.ShortestPath(result, "B", "E");
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
}