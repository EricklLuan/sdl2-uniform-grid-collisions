#pragma once

#include <vector>

#include "object.hpp"

struct Cell {
  std::vector<int> objects_in_cell;
};

class UnifomGrid {
private:
  std::vector<Cell> _grid;
  Vector2 _vSize;
  int _cSize;

  int _getCellID(Vector2 position);
public:

  UnifomGrid(int cell_size, Vector2 viewport_size);

  void add(Object &obj);
  void remove(int id);
  void update(int id);

};