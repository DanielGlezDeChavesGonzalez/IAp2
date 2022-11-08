#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "nodo.hpp"

class Grid {
 public:
    Grid(int n, int m) {
    this->n = n;
    this->m = m;
    for (int i = 0; i < n; i++) {
      std::vector<Nodo> row;
      for (int j = 0; j < m; j++) {
        row.push_back(Nodo(i, j));
      }
      this->grid.push_back(row);
    }
  }

  Nodo get(int i, int j) { return grid[i][j]; }
  void set(int i, int j, int value) { grid[i][j].set_value(value); }

  void print(std::ofstream& out);

  std::vector<Nodo> a_star_euclidean(int x, int y, int x2, int y2);
  std::vector<Nodo> a_star_manhattan(int x, int y, int x2, int y2);

 private:
  int n, m;
  std::vector<std::vector<Nodo>> grid;
};