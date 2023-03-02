#pragma once

#include <SDL2/SDL.h>
#include <variant>
#include <vector>

#include "vector2.hpp"

struct Rect {
  SDL_Rect rect = {
    rand() % 128,
    rand() % 128,
    5,
    5
  };
  bool isColliding = false;
  SDL_Color color = {0, 0, 0, 255};
  Vector2 velocity = { (float)(rand() % 2), (float)(rand() % 2) };
};

class UniformGrid {
private:
  std::vector< std::vector<std::vector<Rect* > > > grid;
  std::vector<Rect> rects;
  int cellSize;

  bool collide(Rect &a, Rect &b);
public:

  UniformGrid(Vector2 viewportSize, int nCellSize);
  ~UniformGrid();

  void addRect(Rect &rect);
  void removeRect(Rect &rect);

  std::vector<Rect*> getCollisions(Rect &rect);
  void checkCollision(Rect &rect);
};  