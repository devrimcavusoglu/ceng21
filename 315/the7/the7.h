#pragma once

#include <climits>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

template <class ForwardIt>
void PrintRange(ForwardIt first, ForwardIt last, std::string delim = "->") {
  if (first == last) {
    return;
  }
  --last;
  for (; first != last; ++first) {
    std::cout << *first << delim;
  }
  std::cout << *first;
}

struct Road {
  std::pair<int, int> endpoints;
  int time;
  Road(std::pair<int, int> eps, int t) : endpoints(eps), time(t) {}
};

void FindRoute(int n, std::vector<Road> roads, int s, int d, int x, int y);