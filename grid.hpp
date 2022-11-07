#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "nodo.hpp"

class Grid {
 public:
  Grid(int n, int m) : n(n), m(m) {
    grid = new Nodo*[n];
    for (int i = 0; i < n; i++) {
      grid[i] = new Nodo[m];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        Nodo* nodo = new Nodo(i, j);
        grid[i][j] = *nodo;
      }
    }
  }

  Nodo get(int i, int j) { return grid[i][j]; }
  void set(int i, int j, int value) { grid[i][j].set_value(value); }

  void print(std::ofstream& out);

  std::vector<Nodo> a_star_euclidean(int x, int y, int x2, int y2);
  std::vector<Nodo> a_star_manhattan(int x, int y, int x2,
                                                    int y2);

 private:
  int n, m;
  Nodo** grid;
};