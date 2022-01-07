#include "the6.h"
// Don't add any additional includes

/*
  N: Number of racers
  updates: Updates you have heard
*/

template <class T>
int search_vector(T elem, std::vector<T> v) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == elem)
      return i;
  }
  return -1;
}

class Graph {
  public:
    Graph(int N);
    void add(std::pair<int, int> pair);
    void batch_add(std::vector<std::pair<int, int>> updates);
    void remove(int key1, int key2);
    bool contains(int key);
    bool has_transition(int key1, int key2);
    void print();
    void topological_sort_recursive(int v, bool visited[], std::stack<int>& aux_stack);
    std::vector<int> topological_sort();
    bool is_cyclic_recursive(int v, bool visited[], bool *recStack);
    std::pair<bool, std::vector<int>> is_cyclic();
    std::vector<std::vector<bool>> get_matrix();
  private:
    std::unordered_map<int, std::vector<int>> umap;
    int total;
};


Graph::Graph(int N) {
  total = N;
  std::pair<int, std::vector<int>> init_pair;
  for (int i = 0; i < N; i++ ) {
    init_pair.first = i;
    init_pair.second = std::vector<int>();
    umap.insert(init_pair);
  }
}

void Graph::batch_add(std::vector<std::pair<int, int>> updates) {
  for (int i = 0; (size_t)i < updates.size(); i++)
    this->add(updates[i]);
}

void Graph::add(std::pair<int, int> pair) {
  int key1 = pair.first;
  int key2 = pair.second;

  if (this->has_transition(key1, key2))
    return;
  umap.at(key1).push_back(key2);

  // To avoid parallelism in the graph, we remove
  // the previous transition. E.g if r1 passed r2,
  // then there cannot be r2 -> r1 transition anymore.
  remove(key2, key1);
}

void Graph::remove(int key1, int key2) {
  std::vector<int> transitions = umap.at(key1);
  int i = search_vector(key2, transitions);
  if (i != -1) 
    umap.at(key1).erase(umap.at(key1).begin() + i);
}

bool Graph::contains(int key) {
    if (umap.find(key) == umap.end())
        return false;
    return true;
}

bool Graph::has_transition(int key1, int key2) {
  std::vector<int> transitions = umap.at(key1);
  for (int i = 0; i < transitions.size(); i++) {
    if (transitions[i] == key2)
      return true;
  }
  return false;
}

void Graph::topological_sort_recursive(int v, bool visited[], std::stack<int>& aux_stack) {
    visited[v] = true;

    std::vector<int> transitions = umap.at(v);
    for (int i = 0; i < transitions.size(); i++) {
       int u = transitions[i];
       if (!visited[u])
            topological_sort_recursive(u, visited, aux_stack);
    }

    aux_stack.push(v);
}

std::vector<int> Graph::topological_sort() {
    std::stack<int> aux_stack;
  
    // initialize aux_stack
    bool* visited = new bool[this->total];
    for (int i = 0; i < this->total; i++)
        visited[i] = false;
  
    for (int i = 0; i < this->total; i++) {
        if (!visited[i])
            topological_sort_recursive(i, visited, aux_stack);
    }

    std::vector<int> sorted_nodes;
    while (!aux_stack.empty()) {
        sorted_nodes.push_back(aux_stack.top());
        aux_stack.pop();
    }
    return sorted_nodes;
}

bool Graph::is_cyclic_recursive(int v, bool visited[], bool *rec_stack) {
    if(visited[v] == false) {
        visited[v] = true;
        rec_stack[v] = true;

        std::vector<int> transitions = umap.at(v);
        for (int i = 0; i < transitions.size(); i++) {
          int u = transitions[i];
          if (!visited[u] && is_cyclic_recursive(u, visited, rec_stack))
              return true;
          else if (rec_stack[u])
              return true;
        }
    }

    rec_stack[v] = false;
    return false;
}

std::pair<bool, std::vector<int>> Graph::is_cyclic() {
    bool *visited = new bool[this->total];
    bool *rec_stack = new bool[this->total];
    for(int i = 0; i < this->total; i++) {
        visited[i] = false;
        rec_stack[i] = false;
    }

    std::vector<int> cycle;
    std::pair<bool, std::vector<int>> result = {false, cycle};
    for(int i = 0; i < this->total; i++)
        if (is_cyclic_recursive(i, visited, rec_stack)) {
          for (int j = 0; j < this->total; j++) {
            if (rec_stack[j])
              cycle.push_back(j);
          }
          int n = cycle.size();
          for (int k = 0; k < n-1; k++) {
            bool valid = this->has_transition(cycle[k], cycle[k+1]);
            if (!valid) {
              cycle.erase(cycle.begin()+k);
              k--;
              n--;
            }
          }
          // insert the cycled node back
          cycle.push_back(cycle[0]);
          result.first = true;
          result.second = cycle;
          break;
        }

    return result;
}

std::vector<std::vector<bool>> Graph::get_matrix() {
  std::vector<std::vector<bool>> matrix(this->total, std::vector<bool> (this->total, false));
  for (int i = 0; i < this->total; i++) {
    std::vector<int> transitions = umap.at(i);
    for (int j = 0; j < transitions.size(); j++) {
      int u = transitions[j];
      matrix[i][u] = true;
    }
  }

  return matrix;
}

void Graph::print() {
  std::cout << "########## Printing transitions ##########\n";
  for (int i = 0; i < total; i++) {
    std::cout << "Racer: " << i << std::endl;
    std::vector<int> transitions = umap.at(i);
    for (int i = 0; i < transitions.size(); i++) {
      std::cout << "--> " << transitions[i] << std::endl;
    }
  }
  std::cout << "########## Printing completed ##########\n";
}


std::pair<bool, std::vector<int>> RaceResult(int N, std::vector<std::pair<int, int>> updates) {
  Graph graph = Graph(N);
  graph.batch_add(updates);
  //graph.print();

  std::pair<bool, std::vector<int>> is_cyclic = graph.is_cyclic();
  if (is_cyclic.first) {
    return {false, is_cyclic.second};
  }
  else {
    std::vector<int> sorted_list = graph.topological_sort();
    return {true, sorted_list};
  }
}
