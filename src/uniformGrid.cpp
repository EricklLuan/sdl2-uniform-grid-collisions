#include "uniformGrid.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>

UnifomGrid::UnifomGrid(int cell_size, Vector2 viewport_size): _cSize(cell_size), _vSize(viewport_size) {
  int width = std::floor(viewport_size.x/cell_size);
  int height = std::floor(viewport_size.y/cell_size);

  for (int i = 0; i < width*height; i++) {
    _grid.push_back(Cell{});
  }
}

void UnifomGrid::add(Object &obj) {
  int startX = std::floor(obj.position.x/_cSize);
  int endX   = std::floor((obj.position.x + obj.size.x)/_cSize);
  int startY = std::floor(obj.position.y/_cSize);
  int endY   = std::floor((obj.position.y + obj.size.y)/_cSize);

  for (int y = startY; y <= endY; y++) {
    for (int x = startX; x <= endX; x++) {
      std::vector<int> &result = _grid[_getCellID(Vector2((float)x, (float(y))))].objects_in_cell;
      if (std::find(result.begin(), result.end(), obj.getID()) == result.end()) {
        result.push_back(obj.getID());
      }
    }
  }
}

void UnifomGrid::remove(int id) {
  
}

void UnifomGrid::update(int id)
{
  
}

int UnifomGrid::_getCellID(Vector2 position) {
  return ((int)position.x * _cSize) + position.y;
}
