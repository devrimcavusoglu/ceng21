#include "the7.h"

template <class T>
int search_vector(T elem, std::vector<T> v) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == elem)
      return i;
  }
  return -1;
}

struct DistanceVertexIdPair
{
    int id;
    int weight;

    // Constructor
    DistanceVertexIdPair(int weight, int id)
    {
        this->id = id;
        this->weight = weight;
    }

    bool operator< (const DistanceVertexIdPair& p) const
    {
        return weight > p.weight;
    }
};


class Graph {
  public:
    Graph(int N, std::vector<Road> roads);
    bool has_transition(int key1, int key2);
    void print();
    int shortestPath2(int i, int j, std::vector<int> k, std::vector<int> &path);
    int shortestPath(int start_id, int end_id, std::vector<int>& orderedVertexIdList);
    int RouteThroughAux(int start, int aux1, int aux2, int end, std::vector<int> &path);
    void appendPath(std::vector<int> &path1, std::vector<int> &path2);
  private:
    std::vector<std::vector<int> > transitions;
    int Vcount;
};

Graph::Graph(int N, std::vector<Road> roads) {
  this->Vcount = N;
  std::vector<int> row;

  // Initialize transition matrix
  // (-1) for representing no edges. 
  for (int i = 0; i < N; i++ ) {
    row.clear();
    for (int j = 0; j < N; j++) {
      row.push_back(-1);
    }
    this->transitions.push_back(row);
  }

  for (int i = 0; i < roads.size(); i++) {
    Road road = roads[i];
    std::pair<int, int> vertices = road.endpoints;
    this->transitions[vertices.first][vertices.second] = road.time;
    this->transitions[vertices.second][vertices.first] = road.time;
  }
}

bool Graph::has_transition(int key1, int key2) {
    if (this->transitions[key1][key2] != -1)
        return true;
    return false;
}

int Graph::shortestPath2(int i, int j, std::vector<int> k, std::vector<int> &path) {
    if (k.empty()) {
        path.push_back(i);
        path.push_back(j);
        return this->transitions[i][j];
    }
}

int Graph::shortestPath(int start_id, int end_id, std::vector<int>& orderedVertexIdList) {

    // Initializing path table & pq
    std::priority_queue<DistanceVertexIdPair> pq;
    DistanceVertexIdPair start_entry = DistanceVertexIdPair(0, start_id);
    pq.push(start_entry);

    std::vector<int> dist;
    std::vector<int> prev;
    std::vector<bool> visited;

    for (int i = 0; i < this->Vcount; i++) {
        if (i == start_id) 
            dist.push_back(0);
        else 
            dist.push_back(INT_MAX);
        visited.push_back(false);
        prev.push_back(-1);
    }

    while (!pq.empty()) {
        DistanceVertexIdPair dv_pair = pq.top(); pq.pop();
        int u = dv_pair.id;
        for (int v = 0; v < Vcount; v++) {
            if (!this->has_transition(u, v))
                continue;
            else if (visited[v]) 
                continue;
            int alt = dist[u] + this->transitions[u][v];
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                DistanceVertexIdPair entry = DistanceVertexIdPair(alt, v);
                pq.push(entry);
            }
        }
        visited[u] = true;
    }

    int prev_vertex_id = end_id;
    while (prev_vertex_id != -1) {
        orderedVertexIdList.insert(orderedVertexIdList.begin(), prev_vertex_id);
        prev_vertex_id = prev[prev_vertex_id];
    }

    return dist[end_id];
}

void Graph::print() {
  std::cout << "########## Printing transitions ##########\n";
  for (int i = 0; i < this->Vcount; i++) {
    std::cout << "Vertex: " << i << std::endl;
    std::vector<int> i_transitions = this->transitions[i];
    for (int j = 0; j < i_transitions.size(); j++) {
      std::cout << "--> " << i_transitions[j] << std::endl;
    }
  }
  std::cout << "########## Printing completed ##########\n";
}

int Graph::RouteThroughAux(int start, int aux1, int aux2, int end, std::vector<int> &path) {
    int dist = INT_MAX;

    std::vector<int> temp_path;

    dist = this->shortestPath(start, aux1, temp_path);
    appendPath(path, temp_path);
    temp_path.clear();

    dist += this->shortestPath(aux1, aux2, temp_path);
    temp_path.erase(temp_path.begin());
    appendPath(path, temp_path);
    temp_path.clear();

    dist += this->shortestPath(aux2, end, temp_path);
    temp_path.erase(temp_path.begin());
    appendPath(path, temp_path);
    temp_path.clear();
    if (dist < 0) dist = INT_MAX;

    return dist;
}

void Graph::appendPath(std::vector<int> &path1, std::vector<int> &path2) {
    // Appends path1 with path2.
    for (int i = 0; i < path2.size(); i++)
        path1.push_back(path2[i]);
}

void FindRoute(int n, std::vector<Road> roads, int s, int d, int x, int y) {
  // You can change these variables. These are here for demo only.
  std::vector<int> path;
  int cost = INT_MAX;

  Graph g = Graph(n, roads);

  std::vector<int> path_xy;
  std::vector<int> path_yx;
  int dist_xy, dist_yx;

  dist_xy = g.RouteThroughAux(s, x, y, d, path_xy);
  dist_yx = g.RouteThroughAux(s, y, x, d, path_yx);

  if (dist_xy < dist_yx) {
    cost = dist_xy;
    path = path_xy;
  }
  else {
   cost = dist_yx;
   path = path_yx; 
  }

  // Your output should be like this. You can change this as long as you keep
  // the output format. PrintRange function helps you print elements of
  // containers with iteratos (e.g., std::vector).
  std::cout << cost << " ";
  PrintRange(path.begin(), path.end());
  std::cout << std::endl;
}
