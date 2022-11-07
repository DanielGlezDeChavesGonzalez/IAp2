#include "grid.hpp"

#include <stdlib.h>

#include <iostream>

// funcion that returns the path from the start to the end using the A*
// algorithm with the euclidean distance as the heuristic
std::vector<Nodo> Grid::a_star_euclidean(int x, int y, int x2, int y2) {
  std::vector<Nodo> path;
  std::vector<Nodo> open_list;
  std::vector<Nodo> closed_list;

  Nodo* start = new Nodo(x, y);
  Nodo* end = new Nodo(x2, y2);

  std::cout << "Start: " << start->get_x() << ", " << start->get_y()
            << std::endl;

  start->set_g(0);
  start->set_h(start->get_euclidean_distance(end));
  start->set_f(start->get_g() + start->get_h());

  open_list.push_back(*start);

  while (open_list.size() > 0) {
    Nodo* current = new Nodo(open_list[0].get_x(), open_list[0].get_y());
    int current_index = 0;
    for (int i = 0; i < open_list.size(); i++) {
      if (open_list[i].get_f() < current->get_f()) {
        current = new Nodo(open_list[i].get_x(), open_list[i].get_y());
        current_index = i;
      }
    }

    std::cout << "Current: " << current->get_x() << ", " << current->get_y()
              << std::endl;

    open_list.erase(open_list.begin() + current_index);
    closed_list.push_back(*current);

    if (current->get_x() == end->get_x() && current->get_y() == end->get_y()) {
      Nodo* current = end;
      while (current->get_x() != start->get_x() ||
             current->get_y() != start->get_y()) {
        path.push_back(*current);
        current = current->get_parent();
      }
      return path;
    }

    std::vector<Nodo> children;
    int new_g;

    if (current->get_x() - 1 >= 0) {
      Nodo* child = new Nodo(current->get_x() - 1, current->get_y());
      if (child->get_value() != 1) {
        children.push_back(*child);
      }
    }
    if (current->get_x() + 1 < n) {
      Nodo* child = new Nodo(current->get_x() + 1, current->get_y());
      if (child->get_value() != 1) {
        children.push_back(*child);
      }
    }
    if (current->get_y() - 1 >= 0) {
      Nodo* child = new Nodo(current->get_x(), current->get_y() - 1);
      if (child->get_value() != 1) {
        children.push_back(*child);
      }
    }
    if (current->get_y() + 1 < m) {
      Nodo* child = new Nodo(current->get_x(), current->get_y() + 1);
      if (child->get_value() != 1) {
        children.push_back(*child);
      }
    }

    for (int i = 0; i < children.size(); i++) {
      for (int j = 0; j < closed_list.size(); j++) {
        if (children[i].get_x() == closed_list[j].get_x() &&
            children[i].get_y() == closed_list[j].get_y()) {
          continue;
        }
      }

      new_g = current->get_g() + 1;

      for (int j = 0; j < open_list.size(); j++) {
        if (children[i].get_x() == open_list[j].get_x() &&
            children[i].get_y() == open_list[j].get_y() &&
            new_g >= open_list[j].get_g()) {
          continue;
        }
      }

      children[i].set_g(new_g);
      children[i].set_h(children[i].get_euclidean_distance(end));
      children[i].set_f(children[i].get_g() + children[i].get_h());
      children[i].set_parent(current);
      open_list.push_back(children[i]);
    }
  }

  std::cout << "Euclide termino:" << std::endl;

  return path;
}

std::vector<Nodo> Grid::a_star_manhattan(int x, int y, int x2, int y2) {
  std::vector<Nodo> path;
  std::vector<Nodo> open_list;
  std::vector<Nodo> closed_list;

  Nodo* start = new Nodo(x, y);
  Nodo* end = new Nodo(x2, y2);

  std::cout << "Start: " << start->get_x() << ", " << start->get_y()
            << std::endl;

  start->set_g(0);
  start->set_h(start->get_manhattan_distance(end));
  start->set_f(start->get_g() + start->get_h());

  open_list.push_back(*start);

  while (open_list.size() > 0) {
    Nodo* current = new Nodo(open_list[0].get_x(), open_list[0].get_y());
    int current_index = 0;
    for (int i = 0; i < open_list.size(); i++) {
      if (open_list[i].get_f() < current->get_f()) {
        current = new Nodo(open_list[i].get_x(), open_list[i].get_y());
        current_index = i;
      }
    }

    std::cout << "Current: " << current->get_x() << ", " << current->get_y()
              << std::endl;

    open_list.erase(open_list.begin() + current_index);
    closed_list.push_back(*current);

    if (current->get_x() == end->get_x() && current->get_y() == end->get_y()) {
      Nodo* current = end;
      while (current->get_x() != start->get_x() ||
             current->get_y() != start->get_y()) {
        path.push_back(*current);
        current = current->get_parent();
      }
      return path;
    }

    std::vector<Nodo> children;
    int new_g;

    if (current->get_x() - 1 >= 0) {
      Nodo* child = new Nodo(current->get_x() - 1, current->get_y());
      if (child->get_value() != 1) {
        children.push_back(*child);
      }
    }
    if (current->get_x() + 1 < n) {
      Nodo* child = new Nodo(current->get_x() + 1, current->get_y());
      if (child->get_value() != 1) {
        children.push_back(*child);
      }
    }
    if (current->get_y() - 1 >= 0) {
      Nodo* child = new Nodo(current->get_x(), current->get_y() - 1);
      if (child->get_value() != 1) {
        children.push_back(*child);
      }
    }
    if (current->get_y() + 1 < m) {
      Nodo* child = new Nodo(current->get_x(), current->get_y() + 1);
      if (child->get_value() != 1) {
        children.push_back(*child);
      }
    }

    for (int i = 0; i < children.size(); i++) {
      for (int j = 0; j < closed_list.size(); j++) {
        if (children[i].get_x() == closed_list[j].get_x() &&
            children[i].get_y() == closed_list[j].get_y()) {
          continue;
        }
      }

      new_g = current->get_g() + 1;

      for (int j = 0; j < open_list.size(); j++) {
        if (children[i].get_x() == open_list[j].get_x() &&
            children[i].get_y() == open_list[j].get_y() &&
            new_g >= open_list[j].get_g()) {
          continue;
        }
      }

      children[i].set_g(new_g);
      children[i].set_h(children[i].get_manhattan_distance(end));
      children[i].set_f(children[i].get_g() + children[i].get_h());
      children[i].set_parent(current);
      open_list.push_back(children[i]);
    }
  }

  std::cout << "Manhattan termino:" << std::endl;

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
