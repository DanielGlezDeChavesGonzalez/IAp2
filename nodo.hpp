#include <math.h>

#include <iostream>

class Nodo {
 public:
  Nodo() : value(0) {}
  Nodo(int x, int y) : x(x), y(y), value(0) {}

  int get_x() { return x; }
  int get_y() { return y; }

  void set_value(int value) { this->value = value; }
  int get_value() { return value; }

  float get_euclidean_distance(Nodo nodo) {
    return sqrt(pow(nodo.get_x() - x, 2) + pow(nodo.get_y() - y, 2));
  }

  float get_manhattan_distance(Nodo nodo) {
    return abs(nodo.get_x() - x) + abs(nodo.get_y() - y);
  }

  void set_f(int f) { this->f = f; }
  int get_f() { return f; }

  void set_g(int g) { this->g = g; }
  int get_g() { return g; }

  void set_h(int h) { this->h = h; }
  int get_h() { return h; }

  void set_parent(Nodo &parent, std::vector<std::vector<Nodo>> &grid_parent) {
    grid_parent[x][y] = parent;
  }
  Nodo &get_parent(std::vector<std::vector<Nodo>> &grid_parent) {
    return grid_parent[x][y];
  }

 private:
  int x, y;
  int value;
  float f, g, h;
};
