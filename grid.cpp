#include "grid.hpp"

#include <stdlib.h>

#include <iostream>

bool contains(std::vector<Nodo> list, Nodo node) {
  for (int i = 0; i < list.size(); i++) {
    if (list[i].get_x() == node.get_x() && list[i].get_y() == node.get_y()) {
      return true;
    }
  }
  return false;
}

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

  Nodo start = grid[x][y];
  Nodo end = grid[x2][y2];

  std::cout << "Start: " << start.get_x() << ", " << start.get_y() << std::endl;

  start.set_g(0);
  start.set_h(start.get_euclidean_distance(end));
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
    int new_g = 0;

    if (current.get_x() - 1 >= 0) {
      children.push_back(grid[current.get_x() - 1][current.get_y()]);
    }
    if (current.get_x() + 1 < n) {
      children.push_back(grid[current.get_x() + 1][current.get_y()]);
    }
    if (current.get_y() - 1 >= 0) {
      children.push_back(grid[current.get_x()][current.get_y() - 1]);
    }
    if (current.get_y() + 1 < m) {
      children.push_back(grid[current.get_x()][current.get_y() + 1]);
    }

    for (int i = 0; i < children.size(); i++) {
      if (children[i].get_x() < 0 || children[i].get_x() >= n ||
          children[i].get_y() < 0 || children[i].get_y() >= m) {
        continue;
      }
      if (grid[children[i].get_x()][children[i].get_y()].get_value() == 1) {
        continue;
      }
      if (contains(closed_list, children[i])) {
        continue;
      }
      if (contains(open_list, children[i])) {
        new_g = current.get_g() + 1;
        for (int j = 0; j < open_list.size(); j++) {
          if (open_list[j].get_x() == children[i].get_x() &&
              open_list[j].get_y() == children[i].get_y()) {
            if (new_g < open_list[j].get_g()) {
              open_list[j].set_g(new_g);
              open_list[j].set_f(open_list[j].get_g() + open_list[i].get_h());
              grid_parent[open_list[j].get_x()][open_list[j].get_y()] = current;
            }
          }
        }
        continue;
      }
      new_g = current.get_g() + 1;
      children[i].set_g(new_g);
      children[i].set_h(children[i].get_euclidean_distance(end));
      children[i].set_f(children[i].get_g() + children[i].get_h());
      grid_parent[children[i].get_x()][children[i].get_y()] = current;
      open_list.push_back(children[i]);
    }
    get_iterations()++;
  }
  return path;
}

// funcion that returns the path from the start to the end using the A*
// algorithm with manhattan distance as the heuristic
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

  Nodo start = grid[x][y];
  Nodo end = grid[x2][y2];

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
    int new_g = 0;

    if (current.get_x() - 1 >= 0) {
      children.push_back(grid[current.get_x() - 1][current.get_y()]);
    }
    if (current.get_x() + 1 < n) {
      children.push_back(grid[current.get_x() + 1][current.get_y()]);
    }
    if (current.get_y() - 1 >= 0) {
      children.push_back(grid[current.get_x()][current.get_y() - 1]);
    }
    if (current.get_y() + 1 < m) {
      children.push_back(grid[current.get_x()][current.get_y() + 1]);
    }

    for (int i = 0; i < children.size(); i++) {
      if (children[i].get_x() < 0 || children[i].get_x() >= n ||
          children[i].get_y() < 0 || children[i].get_y() >= m) {
        continue;
      }
      if (grid[children[i].get_x()][children[i].get_y()].get_value() == 1) {
        continue;
      }
      if (contains(closed_list, children[i])) {
        continue;
      }
      if (contains(open_list, children[i])) {
        new_g = current.get_g() + 1;
        for (int j = 0; j < open_list.size(); j++) {
          if (open_list[j].get_x() == children[i].get_x() &&
              open_list[j].get_y() == children[i].get_y()) {
            if (new_g < open_list[j].get_g()) {
              open_list[j].set_g(new_g);
              open_list[j].set_f(open_list[j].get_g() + open_list[i].get_h());
              grid_parent[open_list[j].get_x()][open_list[j].get_y()] = current;
            }
          }
        }
        continue;
      }
      new_g = current.get_g() + 1;
      children[i].set_g(new_g);
      children[i].set_h(children[i].get_manhattan_distance(end));
      children[i].set_f(children[i].get_g() + children[i].get_h());
      grid_parent[children[i].get_x()][children[i].get_y()] = current;
      open_list.push_back(children[i]);
    }
    get_iterations()++;
  }
  return path;
}

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
