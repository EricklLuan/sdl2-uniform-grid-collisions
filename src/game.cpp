#include "game.hpp"
#include "vector2.hpp"
#include "uniformGrid.hpp"

#include <iostream>
#include <vector>

Game::Game(): window({"Uniform Grid", Vector2(500, 500), Vector2(128, 128)}), init(true) {
  if (!window.init()) {
    std::cout << "Window init failed\n";
    init = false;
  }
}

Game::~Game() {
  
}

void Game::run() {
  if (!init) return;

  UnifomGrid uniform_grid = UnifomGrid(10, window.vSize);

  std::vector<Object> objs = {
    Object({0, 0}, {20, 20}),
    Object({0, 0}, {20, 20}),
    Object({0, 0}, {20, 20}),
    Object({0, 0}, {20, 20}),
    Object({0, 0}, {20, 20}),
  };

  for (int i = 0; i < objs.size(); i++)
  {
    uniform_grid.add(objs[i]);
  }
  

  while (true) {
    Uint32 startTimer = SDL_GetTicks();

    if (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        return;
        break;
      case SDL_KEYDOWN:
        break;
      }
    }

    window.clear();
   
    window.flip();

    int frameTicks = SDL_GetTicks() - startTimer;
    if (frameTicks < 1000/60) {
      SDL_Delay(1000/60 - frameTicks);
    }
  }
}
