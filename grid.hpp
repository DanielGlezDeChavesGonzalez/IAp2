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
    this->grid = std::vector<std::vector<std::pair<Nodo,Nodo>>>(n, std::vector<std::pair<Nodo,Nodo>>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        grid[i][j].first = Nodo(i, j);
        grid[i][j].second = Nodo(-1, -1);
      }
    }
  }

  Nodo& get_node(int i, int j) { return grid[i][j].first; }
  void set_node(int i, int j, int value) { grid[i][j].first.set_value(value); }

  Nodo& get_parent(int i, int j) { return grid[i][j].second; }
  void set_parent(int i, int j, int value) {
    grid[i][j].second.set_value(value);
  }

  int& get_iterations() { return iterations; }

  void print(std::ofstream& out);

  std::vector<Nodo> a_star_euclidean(int x, int y, int x2, int y2);
  std::vector<Nodo> a_star_manhattan(int x, int y, int x2, int y2);

 private:
  int n, m;
  std::vector<std::vector<std::pair<Nodo, Nodo>>> grid;
  int iterations = 0;
};