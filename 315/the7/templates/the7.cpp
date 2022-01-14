#include "the7.h"

void FindRoute(int n, std::vector<Road> roads, int s, int d, int x, int y) {
  // You can change these variables. These are here for demo only.
  std::vector<int> path;
  int cost = INT_MAX;
  // Write your code here...

  // Your output should be like this. You can change this as long as you keep
  // the output format. PrintRange function helps you print elements of
  // containers with iteratos (e.g., std::vector).
  std::cout << cost << " ";
  PrintRange(path.begin(), path.end());
  std::cout << std::endl;
}