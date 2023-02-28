#pragma once

#include "window.hpp"

class Game {
private:
  Window window;
  SDL_Event e;
  bool init;
public:

  Game();
  ~Game();

  void run();
};