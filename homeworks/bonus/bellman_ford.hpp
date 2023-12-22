#pragma once

#include "global.h"
#include "utility.hpp"

#include <climits>
#include <cstdio>
#include <string>

// a structure to represent a weighted edge in graph
struct Edge {
  int src, dest, weight;
};

// a structure to represent a connected, directed and
// weighted graph
struct Graph {
  // V-> Number of vertices, E-> Number of edges
  int V, E;

  // graph is represented as an array of edges.
  struct Edge *edge;
};

// Creates a graph with V vertices and E edges
struct Graph *createGraph(int V, int E) {
  struct Graph *graph = new Graph;
  graph->V = V;
  graph->E = E;
  graph->edge = new Edge[E];
  return graph;
}

// A utility function used to print the solution
void printArr(int dist[], int n) {
  printf("Vertex Distance from Source\n");
  for (int i = 0; i < n; ++i)
    printf("%d \t\t %d\n", i, dist[i]);
}

void printSteps(int **steps, int steps_num, char **vars, int vars_num) {
  for (int i = 0; i < steps_num; ++i) {
    char *var = vars[steps[i][0]];

    printf("%s %d\n", var, steps[i][1]);
  }
}

// A utility function used to print the solution
void printArrWithVar(int dist[], int n, char **vars, int vars_num) {
  // copy dist for sorting
  int *dist_sorted = new int[n];
  for (int i = 0; i < n; ++i)
    dist_sorted[i] = dist[i];

  // copy vars for sorting
  char **vars_sorted = new char *[n];
  for (int i = 0; i < n; ++i) {
    char *tmp = new char[VAR_MAX_SIZE];
    strcpy(tmp, vars[i]);
    vars_sorted[i] = tmp;
    // vars_sorted[i] = vars[i];
  }

  sortDistByVar(dist_sorted, n, vars_sorted, vars_num);

  for (int i = 0; i < n; ++i) {
    char *var = vars_sorted[i];

    int d = dist_sorted[i];

    // if (d != INT_MAX)
    //   printf("%c \t\t %d\n", var, dist_sorted[i]);
    // else
    // printf("%c \t\t -\n", var);

    if (d != INT_MAX)
      printf("%d ", dist_sorted[i]);
    else
      printf("- ");
  }
  printf("\n");
}

// The main function that finds shortest distances from src
// to all other vertices using Bellman-Ford algorithm. The
// function also detects negative weight cycle
bool BellmanFord(struct Graph *graph, int src, int **steps, int *steps_num,
                 int *dist) {
  *steps_num = 0;

  int V = graph->V;
  int E = graph->E;

  // Step 1: Initialize distances from src to all other
  // vertices as INFINITE
  for (int i = 0; i < V; i++)
    dist[i] = INT_MAX;
  dist[src] = 0;

  // Step 2: Relax all edges |V| - 1 times. A simple
  // shortest path from src to any other vertex can have
  // at-most |V| - 1 edges
  for (int i = 1; i <= V - 1; i++) {
    for (int j = 0; j < E; j++) {
      int u = graph->edge[j].src;
      int v = graph->edge[j].dest;
      // printf("u:%d v:%d\n", u, v);
      int weight = graph->edge[j].weight;
      if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        // printf("%d %d\n", v, dist[u] + weight);

        steps[*steps_num][0] = v;
        steps[*steps_num][1] = dist[u] + weight;
        *steps_num += 1;

        dist[v] = dist[u] + weight;
      }
    }
  }

  // Step 3: check for negative-weight cycles. The above
  // step guarantees shortest distances if graph doesn't
  // contain negative weight cycle. If we get a shorter
  // path, then there is a cycle.
  for (int i = 0; i < E; i++) {
    int u = graph->edge[i].src;
    int v = graph->edge[i].dest;
    int weight = graph->edge[i].weight;
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
      // printf("Graph contains negative weight cycle");
      return false; // If negative cycle is detected, simply
                    // return
    }
  }

  // printArr(dist, V);

  return true;
}