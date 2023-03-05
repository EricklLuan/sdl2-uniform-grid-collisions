#pragma once

#include "vector2.hpp"
#include <SDL2/SDL.h>

class Object {
private:
  int mId;
  static int mCouter;

public:
  Vector2 position;
  Vector2 size;
  SDL_Color color = {0, 0, 0, 255};

  Object(Vector2 nPosition, Vector2 nSize);

  int getID();
};