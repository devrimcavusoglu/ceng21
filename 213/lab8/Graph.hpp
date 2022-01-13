#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

using namespace std;

// Data structure to store adjacency list nodes.
struct AdjListNode {
    int v;
    AdjListNode *next;

    AdjListNode(int x, AdjListNode *t) {
        v = x;
        next = t;
    }
};

typedef AdjListNode *link;

// Data structure to store edges.
struct Edge {
    int v, w;

    Edge(int v = -1, int w = -1) : v(v), w(w) {}
};

class Graph {
public:
    Graph(int V, bool digraph = false);

    ~Graph();

    // Getters.
    int V() const { return Vcnt; }
    int E() const { return Ecnt; }
    bool directed() const { return digraph; }

    void insert(Edge e);
    void remove(Edge e);
    bool isVertex(int v);
    int degreeOf(int v);
    void BFS(int v);
    void print();

    /* TODO */
    bool isEdge(int v, int w);

    /* TODO */
    vector<int> adjNodesOf(int v);

    /* TODO */
    void printPath(int v);

private:
    int Vcnt;               // number of nodes in the graph.
    int Ecnt;               // number of edges in the graph.
    bool digraph;           // is the graph directed?

    vector<link> adj;       // an array of pointers to nodes to represent adjacency list.
    vector<int> distance;
    vector<bool> mark;
    vector<int> previous;

    void reset_vectors();
};

#endif //GRAPH_HPP
