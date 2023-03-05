#pragma once

#include <vector>
#include <unordered_map>

#include "object.hpp"

struct Cell {
  std::vector<int> objects_in_cell;
};

class UnifomGrid {
private:
  std::vector<Cell> _grid;
  std::unordered_map<int, Object*> _objects;

  std::unordered_multimap<int, int> _objCell;

  Vector2 _vSize;
  int _cSize;

private:
  int _getCellID(Vector2 position);
  bool _aabb(int id1, int id2);

public:

  UnifomGrid(int cell_size, Vector2 viewport_size);

  void add(Object &obj);
  void remove(int id);
  void update(int id);

  void checkCollision(int id);
};