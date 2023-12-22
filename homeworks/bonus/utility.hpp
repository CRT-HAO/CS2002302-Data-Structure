#pragma once

#include "global.h"
#include <cstdlib>
#include <cstring>
#include <string>

struct Element {
  char *var;
  int dist;
  int index;
};

static int compare(const void *a, const void *b) {
  // setting up rules for comparison

  struct Element *e_a = (struct Element *)a;
  struct Element *e_b = (struct Element *)b;

  return strcmp(e_a->var, e_b->var);
}

void sortDistByVar(int dist[], int n, char **vars, int vars_num) {
  struct Element *e = new struct Element[n];

  for (int i = 0; i < n; ++i) {
    e[i].var = vars[i];
    e[i].dist = dist[i];
    e[i].index = i;
  }

  qsort(e, n, sizeof(struct Element), compare);

  for (int i = 0; i < n; ++i) {
    vars[i] = e[i].var;
    dist[i] = e[i].dist;
  }

  // for (int i = 0; i < n - 1; i++) {
  //   for (int j = 0; j < n - i - 1; j++) {
  //     if (strcmp(vars[j], vars[j + 1])) {
  //       // swap var;
  //       char *var_temp = vars[j];
  //       vars[j] = vars[j + 1];
  //       vars[j + 1] = var_temp;

  //       // swap dist;
  //       int dist_temp = dist[j];
  //       dist[j] = dist[j + 1];
  //       dist[j + 1] = dist_temp;
  //     }
  //   }
  // }
}

void sortDistByVarWithIndex(int dist[], int n, char **vars, int vars_num,
                            int *new_index) {
  for (int i = 0; i < n; ++i)
    new_index[i] = i;

  struct Element *e = new struct Element[n];

  for (int i = 0; i < n; ++i) {
    e[i].var = vars[i];
    e[i].dist = dist[i];
    e[i].index = i;
  }

  qsort(e, n, sizeof(struct Element), compare);

  for (int i = 0; i < n; ++i) {
    vars[i] = e[i].var;
    dist[i] = e[i].dist;
    new_index[i] = e[i].index;
  }

  // for (int i = 0; i < n - 1; ++i) {
  //   for (int j = 0; j < n - i - 1; ++j) {
  //     if (strcmp(vars[j], vars[j + 1])) {
  //       // swap var;
  //       char *var_temp = vars[j];
  //       vars[j] = vars[j + 1];
  //       vars[j + 1] = var_temp;

  //       // swap dist;
  //       int dist_temp = dist[j];
  //       dist[j] = dist[j + 1];
  //       dist[j + 1] = dist_temp;

  //       // swap index
  //       int index_tmp = new_index[j];
  //       new_index[j] = new_index[j + 1];
  //       new_index[j + 1] = index_tmp;
  //     }
  //   }
  // }
}