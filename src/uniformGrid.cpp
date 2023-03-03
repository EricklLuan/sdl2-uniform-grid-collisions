#include "uniformGrid.hpp"

#include <cmath>
#include <algorithm>
#include <iostream>

UniformGrid::UniformGrid(Vector2 cellSize, Vector2 viewportSize): mCellSize(cellSize), mViewportSize(viewportSize) {}

TargetCells UniformGrid::getTargetCells(Vector2 position, Vector2 size) {
  TargetCells target;

  target.x.x = std::floor(position.x / mCellSize.x);
  target.x.y = std::floor((position.x + size.x) / mCellSize.x);
  target.y.x = std::floor(position.y / mCellSize.y);
  target.y.y = std::floor((position.y + size.y) / mCellSize.y);

  return target;
}

UniformGrid::cellID UniformGrid::getCellId(Vector2 cell) {
  return (int)cell.x * (int)mViewportSize.x + (int)cell.y;
}

void UniformGrid::add(Object &obj) {
  const TargetCells target = getTargetCells(obj.position, obj.size);

  for (int i = target.y.x; i <= target.y.y; i++) {
    for (int j = target.x.x; j <= target.x.y; j++) {
      mObjCell.insert(std::make_pair(obj.id, getCellId({(float)j, (float)i})));
      mCellObj.insert(std::make_pair(getCellId({(float)j, (float)i}), obj.id));
    }
  }
  
  mObjects.insert(std::make_pair(obj.id, &obj));
}

void UniformGrid::remove(objectID &id) {
  typename std::unordered_map<objectID, Object*>::iterator it = mObjects.find(id);
  if (it == mObjects.end()) { return; }

  const auto &range = mObjCell.equal_range(id);

  std::for_each(range.first, range.second, [id, this](const std::pair<objectID, cellID> &index){
    const auto &range = mCellObj.equal_range(index.second);

    for (auto i = range.first; i != range.second; ++i) {
      if (i->second == id) {
        mCellObj.erase(i);
        break;
      }
    }
    
  });
  
  mObjCell.erase(id);
  mObjects.erase(it);
}

void UniformGrid::update(objectID &id) {
  auto it = mObjects.find(id);
  if (it == mObjects.end()) {return;}
  
  remove(it->second);
  add(*it->second);

}

void UniformGrid::checkCollision(objectID &id) {
  const auto &range = mObjCell.equal_range(id);

  for (auto i = range.first; i != range.second; i++) {
    std::cout << i->second << "\n";
  }
  
}

bool UniformGrid::aabb(Object &a, Object &b) {
  bool collide = a.position.x < b.position.x + b.size.x &&
           a.position.x + a.size.x > b.position.x &&
           a.position.y < b.position.y + b.size.y &&
           a.size.y + a.position.y > b.position.y;

  if (collide) std::cout << "collide\n";

  return collide;
}
