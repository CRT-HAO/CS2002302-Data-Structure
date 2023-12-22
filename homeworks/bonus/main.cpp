#include "bellman_ford.hpp"
#include "dijkstra.hpp"
#include "global.h"

#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int findVar(char **vars, size_t vars_size, int *vars_num, char *target) {
  for (int i = 0; i < *vars_num; ++i) {
    if (strcmp(vars[i], target) == 0)
      return i;
  }

  // if vars has no space
  if (*vars_num >= vars_size)
    return -1;

  // auto add variable to vars
  // vars[*vars_num] = target;
  memcpy(vars[*vars_num], target, strlen(target));
  *vars_num += 1;

  return (*vars_num - 1);
}

// Driver's code
int main() {
  int V; // Number of vertices in graph
  int E; // Number of edges in graph
  char src_var[VAR_MAX_SIZE];
  int src = 0;

  cin >> V >> E >> src_var;

  int vars_num = 0;
  char **vars = new char *[V];
  for (int i = 0; i < V; ++i) {
    vars[i] = new char[VAR_MAX_SIZE];
    for (int j = 0; j < V; ++j)
      vars[i][j] = '\0';
  }

  struct Graph *bellman_graph = createGraph(V, E);
  src = findVar(vars, V, &vars_num, src_var);

  int **dijk_graph = createGraph(V);

  for (int i = 0; i < E; ++i) {
    char e_src_var[VAR_MAX_SIZE], e_dest_var[VAR_MAX_SIZE];
    int e_weight;
    cin >> e_src_var >> e_dest_var >> e_weight;

    int e_src = findVar(vars, V, &vars_num, e_src_var);
    int e_dest = findVar(vars, V, &vars_num, e_dest_var);

    if (e_src == -1 || e_dest == -1) {
      printf("Error: no space to save variable\n");
      return -1;
    }

    // bellman ford add path
    bellman_graph->edge[i].src = e_src;
    bellman_graph->edge[i].dest = e_dest;
    bellman_graph->edge[i].weight = e_weight;

    // dijkstra add path
    addPath(dijk_graph, e_src, e_dest, e_weight);
  }

  int **steps = new int *[100];
  for (int i = 0; i < 100; i++) {
    steps[i] = new int[2];
  }
  int steps_num = 0;
  int *dist = new int[V];

  bool bellman_valid = BellmanFord(bellman_graph, 0, steps, &steps_num, dist);
  if (bellman_valid) {
    printSteps(steps, steps_num, vars, vars_num);
    printArrWithVar(dist, V, vars, vars_num);
  } else
    printf("invalid input\n");

  int *dijk_srcs = new int[V];
  int *dijk_dist = new int[V];

  bool dijk_valid = dijkstra(V, dijk_graph, src, dijk_srcs, dijk_dist);
  if (dijk_valid)
    printSolution(V, dist, dijk_srcs, vars, vars_num);
  else
    printf("invalid input\n");

  return 0;
}
