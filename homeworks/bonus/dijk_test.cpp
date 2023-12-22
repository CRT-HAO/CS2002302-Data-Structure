#include "dijkstra.hpp"

#include <iostream>

using namespace std;

int main() {
  /* Let us create the example graph discussed above */
  const int v = 9;

  const int test_graph[v][v] = {
      {0, 4, 0, 0, 0, 0, 0, 8, 0},  {4, 0, 8, 0, 0, 0, 0, 11, 0},
      {0, 8, 0, 7, 0, 4, 0, 0, 2},  {0, 0, 7, 0, 9, 14, 0, 0, 0},
      {0, 0, 0, 9, 0, 10, 0, 0, 0}, {0, 0, 4, 14, 10, 0, 2, 0, 0},
      {0, 0, 0, 0, 0, 2, 0, 1, 6},  {8, 11, 0, 0, 0, 0, 1, 0, 7},
      {0, 0, 2, 0, 0, 0, 6, 7, 0}};

  int **graph = createGraph(v);
  for (int i = 0; i < v; ++i) {
    for (int j = 0; j < v; ++j) {
      graph[i][j] = test_graph[i][j];
    }
  }

  int *srcs = new int[v];
  int *dist = new int[v];

  // Function call
  dijkstra(v, graph, 0, srcs, dist);

  return 0;
}