#pragma once

#include <vector>
#include <unordered_map>

#include "vector2.hpp"

struct Object {
  Vector2 position;
  Vector2 size;
  int id;
};

class UniformGrid {
private:
  using cellID = uint32_t;
  using objectID = uint32_t;

  std::unordered_map<objectID, Object> mObjects;
  std::unordered_multimap<objectID, cellID> mObjCell;
  std::unordered_multimap<cellID, objectID> mCellObj;

  Vector2 mCellSize;
  Vector2 mViewportSize;
public:

  UniformGrid(Vector2 cellSize, Vector2 viewportSize);

  void add(Object &obj);
  void remove(Object &obj);

  void update();
};