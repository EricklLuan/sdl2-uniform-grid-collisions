#pragma once

#include <vector>
#include <cmath>
#include <SDL2/SDL.h>

class UniformGrid {
private:
  std::vector<std::vector<SDL_Rect>> grid;
  std::vector<SDL_Rect> rects;
  int cellSize;
public:

  UniformGrid(std::vector<SDL_Rect> &rect);
  ~UniformGrid();

  void addRect();
  void removeRect();

  std::vector<SDL_Rect>& getCollisions(SDL_Rect &rect);
  void checkCollision();
};