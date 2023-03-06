#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "object.hpp"

struct TargetCells {
  int startX, endX;
  int startY, endY;

  bool operator==(TargetCells op) {
    if (this->startX == op.startX && this->endX == op.endX && this->startY == op.startY && this->endY == op.endY) {
      return true;
    }
    return false;
  }

};

struct Cell {
  std::vector<int> objects_in_cell;
};

class UnifomGrid {
private:
  std::unordered_map<int, Cell> _grid;

  std::unordered_map<int, std::unique_ptr<Object> > _old_objects;
  std::unordered_map<int, Object*> _objects;

  std::unordered_multimap<int, int> _objCell;

  Vector2 _vSize;
  int _cSize;

private:
  int _getCellID(Vector2 position);
  bool _aabb(int id1, int id2);

  TargetCells _getTargetCels(Vector2 position, Vector2 size);

public:

  UnifomGrid(int cell_size, Vector2 viewport_size);

  void add(Object &obj);
  void remove(int id);
  void update(int id);

  void checkCollision(int id);
};