#include "Graph.hpp"

#include <iostream>
#include <climits>
#include <queue>

using namespace std;

Graph::Graph(int V, bool d) {
    Vcnt = V;
    Ecnt = 0;
    digraph = d;

    adj.resize(V);
    for (int i = 0 ; i < V ; i++)
        adj[i] = NULL;

    distance.resize(V);
    mark.resize(V);
    previous.resize(V);
    reset_vectors();
}

Graph::~Graph() {
    for (int v = 0 ; v < Vcnt ; v++) {
        while (adj[v]) {
            link t = adj[v]->next;;
            delete adj[v];
            adj[v] = t;
        }
    }
}

void Graph::reset_vectors() {
    for (int v = 0 ; v < Vcnt ; v++) {
        distance[v] = INT_MAX;
        mark[v] = false;
        previous[v] = -1;
    }
}

void Graph::insert(Edge e) {
    int v = e.v;
    int w = e.w;
    adj[v] = new AdjListNode(w, adj[v]);
    if (!digraph)
        adj[w] = new AdjListNode(v, adj[w]);
    Ecnt++;
}

void Graph::remove(Edge e) {
    int v = e.v;
    int w = e.w;
    if (adj[v] == NULL)
        return;
    if (adj[v]->v == w) {
        link tmp = adj[v];
        adj[v] = adj[v]->next;
        delete tmp;
    } else {
        link cur = adj[v];
        while (cur->next) {
            if (cur->next->v == w) {
                link tmp = cur->next;
                cur = tmp->next;
                delete tmp;
                break;
            } else
                cur = cur->next;
        }
    }
    Ecnt--;
}

bool Graph::isVertex(int v) {
    return (v >= 0 && v < Vcnt);
}

int Graph::degreeOf(int v) {
    link p = adj[v];
    int c = 0;
    while (p != NULL) {
        c++;
        p = p->next;
    }
    return c;
}

void Graph::BFS(int s) {
    queue<int> q;
    vector<int> adjNodes;
    reset_vectors();
    distance[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        adjNodes = adjNodesOf(v);
        for (int w = 0; w < adjNodes.size(); w++) {
            if (distance[adjNodes[w]] == INT_MAX) {
                distance[adjNodes[w]] = distance[v] + 1;
                previous[adjNodes[w]] = v;
                q.push(adjNodes[w]);
            }
        }
    }
}

void Graph::print() {
    cout << Vcnt << " vertices, " << Ecnt << " edges: " << endl;
    for (int v = 0; v < Vcnt; v++) {
        cout << v << ": ";
        link ptr = adj[v];
        while (ptr) {
            cout << ptr->v << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }
}

bool Graph::isEdge(int v, int w) {
    std::vector<int> adjNodes;
    adjNodes = this->adjNodesOf(v);
    for (int i = 0; i < adjNodes.size(); i++) {
        int u_id = adjNodes[i];
        if (u_id == w)
            return true;
    }
    return false;
}

vector<int> Graph::adjNodesOf(int v) {
    std::vector<int> adjNodes;
    AdjListNode *current_node = adj[v];

    while (current_node) {
        adjNodes.push_back(current_node->v);
        current_node = current_node->next;
    }
    return adjNodes;
}

void Graph::printPath(int v) {
    std::vector<int> current_path;
    int prev_dist = INT_MAX;

    if (this->previous[v] == -1)
            current_path.push_back(v);
    else if (this->distance[v] < prev_dist) {
        int prev_node = v;
        while (prev_node != -1) {
            current_path.insert(current_path.begin(), prev_node);
            prev_node = this->previous[prev_node];
        }
        prev_dist = this->distance[v];
    }

    // Print the shortest path
    for (int i = 0; i < current_path.size(); i++)
        std::cout << current_path[i] << " ";
}
