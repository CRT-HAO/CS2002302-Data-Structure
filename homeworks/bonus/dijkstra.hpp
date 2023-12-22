#pragma once

#include "global.h"
#include "utility.hpp"

#include <climits>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string>

void addPath(int **graph, int src, int dest, int weight) {
  graph[src][dest] = weight;
}

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int V, int dist[], bool sptSet[]) {
  // Initialize min value
  int min = INT_MAX, min_index;

  for (int v = 0; v < V; v++)
    if (sptSet[v] == false && dist[v] <= min)
      min = dist[v], min_index = v;

  return min_index;
}

void getPath(int V, int *srcs, char **vars, int vars_num, int index,
             std::string &path) {
  char *var = vars[index];

  if (srcs[index] == index) {
    path = var + path;
    return;
  }

  std::string tmp = " -> ";
  tmp += var;

  path = tmp + path;

  getPath(V, srcs, vars, vars_num, srcs[index], path);
}

// A utility function to print the constructed distance
// array
void printSolution(int V, int dist[], int *srcs, char **vars, int vars_num) {
  int *dist_sorted = new int[V];
  for (int i = 0; i < V; ++i)
    dist_sorted[i] = dist[i];

  // copy vars for sorting
  char **vars_sorted = new char *[V];
  for (int i = 0; i < V; ++i) {
    char *tmp = new char[VAR_MAX_SIZE];
    strcpy(tmp, vars[i]);
    vars_sorted[i] = tmp;
  }

  // copy srcs for sorting
  int *srcs_sorted = new int[V];
  for (int i = 0; i < V; ++i)
    srcs_sorted[i] = srcs[i];

  int *new_index = new int[V];
  sortDistByVarWithIndex(dist_sorted, V, vars_sorted, vars_num, new_index);

  for (int i = 0; i < V; ++i) {
    if (dist_sorted[i] == INT_MAX) {
      printf("No path to %s\n", vars_sorted[i]);
      continue;
    }

    std::string path = " = ";
    path += std::to_string(dist_sorted[i]);

    getPath(V, srcs, vars, vars_num, new_index[i], path);

    printf("%s\n", path.c_str());
  }

  // printf("Vertex \t\t Distance from Source\n");
  // for (int i = 0; i < V; i++)
  //   printf("%d \t\t\t\t %d\n", i, dist_sorted[i]);
}

int **createGraph(int V) {
  int **graph = new int *[V];
  for (int i = 0; i < V; ++i) {
    graph[i] = new int[V];
    for (int j = 0; j < V; ++j)
      graph[i][j] = 0;
  }

  return graph;
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
bool dijkstra(int V, int **graph, int src, int *srcs, int *dist) {
  for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
      if (graph[i][j] < 0)
        return false;
    }
  }

  bool *sptSet = new bool[V]; // sptSet[i] will be true if vertex i is
                              // included in shortest
  // path tree or shortest distance from src to i is
  // finalized

  // Initialize all distances as INFINITE and stpSet[] as
  // false
  for (int i = 0; i < V; i++)
    dist[i] = INT_MAX, sptSet[i] = false;

  // Distance of source vertex from itself is always 0
  dist[src] = 0;
  srcs[src] = src;

  // Find shortest path for all vertices
  for (int count = 0; count < V - 1; count++) {
    // Pick the minimum distance vertex from the set of
    // vertices not yet processed. u is always equal to
    // src in the first iteration.
    int u = minDistance(V, dist, sptSet);

    // Mark the picked vertex as processed
    sptSet[u] = true;

    // Update dist value of the adjacent vertices of the
    // picked vertex.
    for (int v = 0; v < V; v++)

      // Update dist[v] only if is not in sptSet,
      // there is an edge from u to v, and total
      // weight of path from src to  v through u is
      // smaller than current value of dist[v]
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
          dist[u] + graph[u][v] < dist[v]) {
        dist[v] = dist[u] + graph[u][v];
        srcs[v] = u;
      }
  }

  // print the constructed distance array
  // printSolution(V, dist);

  // for (int i = 0; i < V; ++i) {
  //   printf("%d: from=%d, dist=%d\n", i, srcs[i], dist[i]);
  // }

  // release memory
  delete[] sptSet;

  return true;
}