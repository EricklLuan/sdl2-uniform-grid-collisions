#pragma once

#include "vector2.hpp"

class Object {
private:
  int mId;
  static int mCouter;

public:
  Vector2 position;
  Vector2 size;

  Object(Vector2 nPosition, Vector2 nSize);

  int getID();
};