#include <climits>
#include <iostream>

using namespace std;

void findLeafNode(int **matrix, size_t matrix_size, int *leafs,
                  size_t *leafs_size) {
  *leafs_size = 0;
  for (size_t i = 0; i < matrix_size; ++i)
    leafs[i] = -1;

  for (size_t i = 0; i < matrix_size; ++i) {
    int degree = 0;
    size_t parent = 0;
    for (size_t j = 0; j < matrix_size; ++j) {
      if (matrix[i][j] > 0 && j != i) {
        ++degree;
        parent = j;
      }
    }

    if (degree == 1) {
      // degree equal to 1 means it's a leaf node

      int parent_degree = 0;
      for (size_t j = 0; j < matrix_size; ++j) {
        if (matrix[parent][j] > 0 && j != i) {
          ++parent_degree;
        }
      }

      if (parent_degree <= 1)
        continue;

      leafs[*leafs_size] = i;
      *leafs_size += 1;
    }
  }
}

void deleteNode(int **matrix, size_t matrix_size, int target) {
  for (size_t i = 0; i < matrix_size; ++i) {
    matrix[target][i] = 0;
  }

  for (size_t i = 0; i < matrix_size; ++i) {
    matrix[i][target] = 0;
  }
}

void findMHTRoots(int **matrix, size_t matrix_size, int *roots,
                  size_t *roots_num) {
  *roots_num = 0;

  for (size_t i = 0; i < matrix_size; ++i) {
    int degree = 0;
    for (size_t j = 0; j < matrix_size; ++j) {
      if (matrix[i][j] > 0)
        ++degree;
    }

    if (degree >= 1) {
      roots[*roots_num] = int(i);
      *roots_num += 1;
    }
  }
}

void printMatrix(int **matrix, size_t matrix_size) {
  for (size_t i = 0; i < matrix_size; ++i) {
    for (size_t j = 0; j < matrix_size; ++j) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  int nodes_num;
  cin >> nodes_num;
  const int edges_num = (nodes_num - 1);

  // declare matrix 2d array
  int **matrix = new int *[nodes_num];
  for (int i = 0; i < nodes_num; ++i)
    matrix[i] = new int[nodes_num];

  for (int i = 0; i < nodes_num; ++i) {
    matrix[i][i] = 1;
  }

  for (int i = 0; i < edges_num; ++i) {
    int from, to;
    cin >> from >> to;
    matrix[from][to] = 1;
    matrix[to][from] = 1;
  }

  // printMatrix(matrix, nodes_num);

  for (;;) {
    int *leafs = new int[nodes_num];
    size_t leafs_num = 0;
    findLeafNode(matrix, nodes_num, leafs, &leafs_num);
    if (leafs_num == 0)
      break;

    // cout << "leafs: ";
    for (size_t i = 0; i < leafs_num; ++i) {
      // cout << leafs[i] << ", ";
      deleteNode(matrix, nodes_num, leafs[i]);
    }
    // cout << endl;
    // printMatrix(matrix, nodes_num);
  }

  // printMatrix(matrix, nodes_num);

  int *roots = new int[nodes_num];
  size_t roots_num = 0;
  findMHTRoots(matrix, nodes_num, roots, &roots_num);
  for (size_t i = 0; i < roots_num; ++i) {
    cout << roots[i] << " ";
  }
  cout << endl;

  return 0;
}