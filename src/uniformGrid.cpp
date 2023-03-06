#include "uniformGrid.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>

UnifomGrid::UnifomGrid(int cell_size, Vector2 viewport_size): _cSize(cell_size), _vSize(viewport_size) {
}

void UnifomGrid::add(Object &obj) {
  int startX = std::floor(obj.position.x/_cSize);
  int endX   = std::floor((obj.position.x + obj.size.x)/_cSize);
  int startY = std::floor(obj.position.y/_cSize);
  int endY   = std::floor((obj.position.y + obj.size.y)/_cSize);

  for (int y = startY; y <= endY; y++) {
    for (int x = startX; x <= endX; x++) {
      int cellId = _getCellID(Vector2((float)x, (float(y))));

      std::vector<int> &result = _grid[cellId].objects_in_cell;
      _objCell.insert(std::make_pair(obj.getID(), cellId));

      if (std::find(result.begin(), result.end(), obj.getID()) == result.end()) {
        result.push_back(obj.getID());
      }
    }
  }

  _objects[obj.getID()] = &obj;
}

void UnifomGrid::remove(int id) {
  if (_objects.find(id) == _objects.end()) return;

  const auto &range = _objCell.equal_range(id);

  for (auto i = range.first; i != range.second; i++) {

    std::vector<int> &cell = _grid[i->second].objects_in_cell;
    const auto it = std::find(cell.begin(), cell.end(), id);
    if (it != cell.end()) {
      _grid[i->second].objects_in_cell.erase(cell.begin() + (it - cell.begin()));
    }
  }

  _objCell.erase(id);
}

void UnifomGrid::update(int id) {
  remove(id);
  add(*_objects[id]);
}

void UnifomGrid::checkCollision(int id) {
  if (_objects.find(id) == _objects.end()) return;

  const auto &range = _objCell.equal_range(id);

  for (auto i = range.first; i != range.second; i++) {
    std::vector<int> &cell = _grid[i->second].objects_in_cell;
    
    for (int j = 0; j < cell.size(); j++) {
      if (cell[j] != id) {
        if (_aabb(id, cell[j])) {
          _objects[id]->color = {0, 255, 0, 255};
        } 
      }
    }
  }
}

int UnifomGrid::_getCellID(Vector2 position) {
  return ((int)position.x * _cSize) + position.y;
}

bool UnifomGrid::_aabb(int id1, int id2) {
  Object* box1 = _objects[id1];
  Object* box2 = _objects[id2];

  return box1->position.x < box2->position.x + box2->size.x &&
           box1->position.x + box1->size.x > box2->position.x &&
           box1->position.y < box2->position.y + box2->size.y &&
           box1->size.y + box1->position.y > box2->position.y;
  
}
