#include "Graph.h"
#include "GraphExceptions.h"
#include <iostream>


void print_test_begin(std::string test_name) {
    std::cout << "#### TEST " << test_name << " BEGIN ####\n";
}

void print_test_end() {
    std::cout << "############### TEST END ###############\n";
}

void test_insert_vertices(Graph &g) {
    print_test_begin("insert vertices");

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
    g.printVertices();

    print_test_end();
}

void test_connect_vertices(Graph &g) {
    print_test_begin("connect vertices");
    g.ConnectVertices("A", "B", 1);
    g.ConnectVertices("A", "C", 3);
    g.ConnectVertices("B", "C", 1);
    g.ConnectVertices("B", "D", 2);
    g.ConnectVertices("C", "D", 5);
    g.ConnectVertices("C", "E", 1);
    g.ConnectVertices("D", "E", 3);

    g.ConnectVertices("B", "F", 3);
    g.ConnectVertices("F", "G", 1);
    g.ConnectVertices("G", "E", 2);
    g.PrintAll();
    print_test_end();
}

void test_shortest_path(Graph &g) {
    print_test_begin("shortest path");
    std::vector<int> result;
    g.ShortestPath(result, "B", "E");
    for (int i = 0; i < result.size(); i++) 
            std::cout << result[i] << " ";
    std::cout << std::endl;
    print_test_end();
}

void test_modify_nonexisting_edge(Graph &g) {
    print_test_begin("modify nonexisting edge");
    std::cout << "Modify (A,B) as 3 from 1.\n";
    g.ModifyEdge("A", "B", 3);
    std::cout << "Modify (A,E) as 5 (non-existing edge).\n";
    g.ModifyEdge("A", "E", 5);
    std::cout << "Modify (X,Y) as 5 (non-existing edge & non-existing vertices).\n";
    try {
        g.ModifyEdge("X", "Y", 5);
    }
    catch (std::runtime_error& exception) {
        std::cout << exception.what() << std::endl;
    }
    print_test_end();
}


void test_multiple_shortest_path(Graph &g) {
    print_test_begin("multiple shortest paths");
    std::vector<std::vector<int> > result;
    g.MultipleShortPaths(result, "B", "E", 3);
    for (int i = 0; i < result.size(); i++) {
        std::vector<int> current_path = result[i];
        std::cout << "Path " << i << std::endl;
        for (int j = 0; j < current_path.size(); j++)
            std::cout << current_path[j] << " ";
        std::cout << std::endl;
    }
    print_test_end();
}


int main()
{
    Graph g;

    test_insert_vertices(g);
    test_connect_vertices(g);
    test_shortest_path(g);
    test_modify_nonexisting_edge(g);
    test_multiple_shortest_path(g);
    
}