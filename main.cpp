#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "grid.hpp"

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "Error: no se ingresaron los parametros necesarios"
              << std::endl;
    std::cout << "Ejecutar: ./main <archivo de salida euclidea> <archivo de "
                 "salida manhattan>"
              << std::endl;
    return 1;
  }
  std::ofstream out(argv[1]);
  std::ofstream out2(argv[2]);
  bool ejecutar = true;
  int n, m;

  while (ejecutar) {
    std::cout << "Introduce n y m de la matriz: " << std::endl;
    std::cin >> n >> m;

    Grid grid(n, m);
    Grid grid2(n, m);

    int x, y, x2, y2;
    std::cout << "Introduce x, y, x2, y2: " << std::endl;
    std::cin >> x >> y >> x2 >> y2;

    grid.set_node(x - 1, y - 1, 1);
    grid.set_node(x2 - 1, y2 - 1, 2);

    grid2.set_node(x - 1, y - 1, 1);
    grid2.set_node(x2 - 1, y2 - 1, 2);

    std::vector<Nodo> path =
        grid.a_star_euclidean(x - 1, y - 1, x2 - 1, y2 - 1);
    for (int i = 0; i < path.size(); i++) {
      if (path[i].get_x() == x - 1 && path[i].get_y() == y - 1) {
        continue;
      }
      if (path[i].get_x() == x2 - 1 && path[i].get_y() == y2 - 1) {
        continue;
      }
      grid.set_node(path[i].get_x(), path[i].get_y(), 3);
    }
    out << "Euclidean: " << grid.get_iterations() << std::endl;
    grid.print(out);

    std::vector<Nodo> path_manhattan =
        grid2.a_star_manhattan(x - 1, y - 1, x2 - 1, y2 - 1);
    for (int i = 0; i < path_manhattan.size(); i++) {
      if (path[i].get_x() == x - 1 && path[i].get_y() == y - 1) {
        continue;
      }
      if (path[i].get_x() == x2 - 1 && path[i].get_y() == y2 - 1) {
        continue;
      }
      grid2.set_node(path_manhattan[i].get_x(), path_manhattan[i].get_y(), 3);
    }
    out2 << "Manhattan: " << grid2.get_iterations() << std::endl;
    grid2.print(out2);

    std::cout << "Quieres seguir ejecutando? (1/0)" << std::endl;
    std::cin >> ejecutar;
  }

  return 0;
}