#include <math.h>

#include <iostream>

class Nodo {
 public:
  Nodo() : value(0) {}
  Nodo(int x, int y) : x(x), y(y), value(0) {}

  int get_x() { return x; }
  int get_y() { return y; }

  void set_parent(Nodo* parent) { this->parent = parent; }
  Nodo* get_parent() { return parent; }

  void set_value(int value) { this->value = value; }
  int get_value() { return value; }

  int get_euclidean_distance(Nodo* nodo) {
    return sqrt(pow(nodo->get_x() - x, 2) + pow(nodo->get_y() - y, 2));
  }

  int get_manhattan_distance(Nodo* nodo) {
    return abs(nodo->get_x() - x) + abs(nodo->get_y() - y);
  }

  void set_f(int f) { this->f = f; }
  int get_f() { return f; }

  void set_g(int g) { this->g = g; }
  int get_g() { return g; }

  void set_h(int h) { this->h = h; }
  int get_h() { return h; }

 private:
  int x, y;
  Nodo* parent;
  int value;
  int f, g, h;
};
