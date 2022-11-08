#include "grid.hpp"

#include <stdlib.h>

#include <iostream>

// funcion that returns the path from the start to the end using the A*
// algorithm with the euclidean distance as the heuristic
std::vector<Nodo> Grid::a_star_euclidean(int x, int y, int x2, int y2) {
  std::vector<Nodo> path;
  std::vector<Nodo> open_list;
  std::vector<Nodo> closed_list;
  std::vector<std::vector<Nodo>> grid_parent(n, std::vector<Nodo>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      grid_parent[i][j] = Nodo(-1, -1);
    }
  }

  Nodo start(x, y);
  Nodo end(x2, y2);

  std::cout << "Start: " << start.get_x() << ", " << start.get_y() << std::endl;

  start.set_g(0);
  start.set_h(start.get_euclidean_distance(end));
  start.set_f(start.get_g() + start.get_h());

  open_list.push_back(start);

  while (open_list.size() > 0) {
    // for (int i = 0; i < open_list.size(); i++) {
    //   std::cout << "open_list[" << i << "]: " << open_list[i].get_x() << ", "
    //             << open_list[i].get_y() << std::endl;
    // }
    // std::cout << "----------------" << std::endl;
    // for (int i = 0; i < closed_list.size(); i++) {
    //   std::cout << "closed_list[" << i << "]: " << closed_list[i].get_x()
    //             << ", " << closed_list[i].get_y() << std::endl;
    // }
    Nodo current = open_list[0];
    int current_index = 0;
    for (int i = 0; i < open_list.size(); i++) {
      if (open_list[i].get_f() < current.get_f()) {
        current = open_list[i];
        current_index = i;
      }
    }
    open_list.erase(open_list.begin() + current_index);
    closed_list.push_back(current);

    if (current.get_x() == end.get_x() && current.get_y() == end.get_y()) {
      Nodo current = end;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          std::cout << "(" << grid_parent[i][j].get_x() + 1 << ", "
                    << grid_parent[i][j].get_y() + 1 << ")";
        }
        std::cout << std::endl;
      }
      while (current.get_x() != start.get_x() ||
             current.get_y() != start.get_y()) {
        for (int i = 0; i < path.size(); i++) {
          std::cout << "path[" << i << "]: " << path[i].get_x() << ", "
                    << path[i].get_y() << std::endl;
        }
        path.push_back(current);
        current = grid_parent[current.get_x()][current.get_y()];
      }
      path.push_back(start);
      return path;
    }

    std::vector<Nodo> children;
    int new_g;

    children.push_back(Nodo(current.get_x() + 1, current.get_y()));
    children.push_back(Nodo(current.get_x() - 1, current.get_y()));
    children.push_back(Nodo(current.get_x(), current.get_y() + 1));
    children.push_back(Nodo(current.get_x(), current.get_y() - 1));

    for (int i = 0; i < children.size(); i++) {
      Nodo child = children[i];
      if (child.get_x() > n - 1 || child.get_x() < 0 || child.get_y() > m - 1 ||
          child.get_y() < 0) {
        continue;
      }
      if (child.get_x() == start.get_x() && child.get_y() == start.get_y()) {
        continue;
      }

      new_g = current.get_g() + 1;
      for (int j = 0; j < closed_list.size(); j++) {
        if (child.get_x() == closed_list[j].get_x() &&
            child.get_y() == closed_list[j].get_y()) {
          continue;
        }
      }
      for (int j = 0; j < open_list.size(); j++) {
        if (child.get_x() == open_list[j].get_x() &&
            child.get_y() == open_list[j].get_y()) {
          continue;
        }
      }
      child.set_g(new_g);
      child.set_h(child.get_euclidean_distance(end));
      child.set_f(child.get_g() + child.get_h());
      open_list.push_back(child);
      grid_parent[child.get_x()][child.get_y()] = current;
    }
  }
}

std::vector<Nodo> Grid::a_star_manhattan(int x, int y, int x2, int y2) {
  std::vector<Nodo> path;
  std::vector<Nodo> open_list;
  std::vector<Nodo> closed_list;
  std::vector<std::vector<Nodo>> grid_parent(n, std::vector<Nodo>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      grid_parent[i][j] = Nodo(-1, -1);
    }
  }

  Nodo start(x, y);
  Nodo end(x2, y2);

  std::cout << "Start: " << start.get_x() << ", " << start.get_y() << std::endl;

  start.set_g(0);
  start.set_h(start.get_manhattan_distance(end));
  start.set_f(start.get_g() + start.get_h());

  open_list.push_back(start);

  while (open_list.size() > 0) {
    Nodo current = open_list[0];
    int current_index = 0;
    for (int i = 0; i < open_list.size(); i++) {
      if (open_list[i].get_f() < current.get_f()) {
        current = open_list[i];
        current_index = i;
      }
    }
    open_list.erase(open_list.begin() + current_index);
    closed_list.push_back(current);

    if (current.get_x() == end.get_x() && current.get_y() == end.get_y()) {
      Nodo current = end;
      while (current.get_x() != start.get_x() ||
             current.get_y() != start.get_y()) {
        path.push_back(current);
        current = grid_parent[current.get_x()][current.get_y()];
      }
      path.push_back(start);
      return path;
    }

    std::vector<Nodo> children;
    int new_g;

    children.push_back(Nodo(current.get_x() + 1, current.get_y()));
    children.push_back(Nodo(current.get_x() - 1, current.get_y()));
    children.push_back(Nodo(current.get_x(), current.get_y() + 1));
    children.push_back(Nodo(current.get_x(), current.get_y() - 1));

    for (int i = 0; i < children.size(); i++) {
      Nodo child = children[i];
      if (child.get_x() > n - 1 || child.get_x() < 0 || child.get_y() > m - 1 ||
          child.get_y() < 0) {
        continue;
      }
      if (child.get_value() == 1) {
        continue;
      }
      new_g = current.get_g() + 1;
      if (new_g < child.get_g()) {
        child.set_g(new_g);
        child.set_h(child.get_manhattan_distance(end));
        child.set_f(child.get_g() + child.get_h());
        child.set_parent(current, grid_parent);
        open_list.push_back(child);
      }
    }
  }
  return path;
};

void Grid::print(std::ofstream& out) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      out << "|";
      switch (grid[i][j].get_value()) {
        case 0:
          out << " ";
          break;
        case 1:
          out << "S";
          break;
        case 2:
          out << "F";
          break;
        case 3:
          out << "X";
          break;

        default:
          out << " ";
          break;
      }
    }
    out << "|" << std::endl;
  }
}
