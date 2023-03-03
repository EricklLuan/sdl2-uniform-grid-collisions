#pragma once

#include <unordered_map>

#include "vector2.hpp"

struct Object {
  Vector2 position;
  Vector2 size;

  Object* id = this;
};

struct TargetCells {
  Vector2 x;
  Vector2 y;
};

class UniformGrid {
private:
  using cellID = uint32_t;
  using objectID = Object*;

  std::unordered_map<objectID, Object*> mObjects;

  // Uma chave pode receber diversos valores
  std::unordered_multimap<objectID, cellID> mObjCell;
  std::unordered_multimap<cellID, objectID> mCellObj;

  Vector2 mCellSize;
  Vector2 mViewportSize;
private:
  cellID getCellId(Vector2 cell);

public:

  TargetCells getTargetCells(Vector2 position, Vector2 size);
  UniformGrid(Vector2 cellSize, Vector2 viewportSize);

  void add(Object &obj);
  void remove(objectID &id);

  void update(objectID &id);
  void checkCollision(objectID &id);

  bool aabb(Object &a, Object &b);
};