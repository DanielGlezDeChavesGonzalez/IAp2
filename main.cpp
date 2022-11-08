#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "grid.hpp"

int main(int argc, char** argv) {
  std::ofstream out(argv[1]);

  int n = 20, m = 20;
  std::cout << "Introduce n y m de la matriz: " << std::endl;

  // std::cin >> n >> m;
  Grid grid(n, m);

  // for (int i = 0; i < n; i++) {
  //   g.set(i, m / 2, 3);
  // }

  int x, y, x2, y2;
  std::cout << "Introduce x, y, x2, y2: " << std::endl;
  // std::cin >> x >> y >> x2 >> y2;
  x = 2;
  y = 2;
  x2 = 15;
  y2 = 15;

  grid.set(x - 1, y - 1, 1);
  grid.set(x2 - 1, y2 - 1, 2);

  std::vector<Nodo> path = grid.a_star_euclidean(x - 1, y - 1, x2 - 1, y2 - 1);
  for (int i = 0; i < path.size(); i++) {
    if (path[i].get_x() == x - 1 && path[i].get_y() == y - 1) {
      continue;
    }
    if (path[i].get_x() == x2 - 1 && path[i].get_y() == y2 - 1) {
      continue;
    }
    grid.set(path[i].get_x(), path[i].get_y(), 3);
  }
  out << "Euclidean" << std::endl;
  grid.print(out);
  std::cout << "Euclidean" << std::endl;
  for (int i = 0; i < path.size(); i++) {
    std::cout << "(" << path[i].get_x() << ", " << path[i].get_y() << ")"
              << std::endl;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cout << grid.get(i, j).get_value() << " ";
    }
    std::cout << std::endl;
  }

  // std::vector<Nodo> path_manhattan =
  //     grid.a_star_manhattan(x - 1, y - 1, x2 - 1, y2 - 1);
  // for (int i = 0; i < path_manhattan.size(); i++) {
  //   grid.set(path_manhattan[i].get_x(), path_manhattan[i].get_y(), 3);
  // }
  // out << "Manhattan:" << std::endl;
  // grid.print(out);
  return 0;
}