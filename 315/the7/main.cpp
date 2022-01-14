#include "the7.h"
#include <fstream>
#include <sstream>
#include <string>

namespace {
struct Params {
  int n;
  std::vector<Road> roads;
  int s, d, x, y;
};

// Reads .test files and fills a `Params` struct.
// .test file consists of following items. Each element in the below list is on
// their separate lines.
//
// <number-of-houses(N)>
// <student-house-id(S)> <supervisor-house-id(D)>
// <juror#1-house-id(X)> <juror#2-house-id(X)>
// <number-of-roads(M)>
// <endpoint#1> <endpoint#2> <length>  <-- Repeats m times
Params ReadTestCase(std::string filename) {
  Params params;
  params.n = 0;
  params.roads.clear();
  std::ifstream ftest(filename);
  if (ftest.fail()) {
    std::cerr << "[X] Error opening test file! Exiting.\n";
    exit(1);
  }
  try {
    std::string line;
    std::getline(ftest, line);
    std::istringstream iss(line);
    iss >> params.n;

    std::getline(ftest, line);
    iss.clear();
    iss = std::istringstream(line);
    iss >> params.s >> params.d;

    std::getline(ftest, line);
    iss.clear();
    iss = std::istringstream(line);
    iss >> params.x >> params.y;

    std::getline(ftest, line);
    iss.clear();
    iss = std::istringstream(line);
    int m;
    iss >> m;
    iss.clear();
    params.roads.reserve(m);
    for (int i = 0; i < m; i++) {
      std::getline(ftest, line);
      std::istringstream iss(line);
      int u, v, w;
      iss >> u >> v >> w;
      params.roads.push_back(Road({u, v}, w));
    }

  } catch (...) {
    std::cerr << "[X] Error reading test file! Exiting.\n";
    exit(2);
  }
  return params;
}
} // namespace

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: %s file\n", argv[0]);
    printf("arguments:\n  file:\tPath to the input file.\n");
    exit(0);
  }
  auto p = ReadTestCase(argv[1]);
  FindRoute(p.n, p.roads, p.s, p.d, p.x, p.y);
  return 0;
}
