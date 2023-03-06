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

  UnifomGrid uniform_grid = UnifomGrid(15, window.vSize);

  std::vector<Object> objs = {
    Object({0, 0}, {20, 20}),
    Object({0, 0}, {20, 20}),
    Object({(float)(rand() % (128 - 20)), (float)(rand() % (128 - 20))}, {20, 20}),
    Object({(float)(rand() % (128 - 20)), (float)(rand() % (128 - 20))}, {20, 20}),
    Object({(float)(rand() % (128 - 20)), (float)(rand() % (128 - 20))}, {20, 20}),
  };

  while (true) {
    Uint32 startTimer = SDL_GetTicks();

    if (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        return;
        break;
      case SDL_KEYDOWN:
        if (e.key.repeat == 0) {
          if (e.key.keysym.scancode == SDL_SCANCODE_D) objs[0].position.x += 1;
          if (e.key.keysym.scancode == SDL_SCANCODE_A) objs[0].position.x -= 1;
          if (e.key.keysym.scancode == SDL_SCANCODE_W) objs[0].position.y -= 1;
          if (e.key.keysym.scancode == SDL_SCANCODE_S) objs[0].position.y += 1;
        }
        break;
      }
    }

    window.clear();
   
    for (int i = 0; i < objs.size(); i++) {

      SDL_Rect rect = {
        (int)objs[i].position.x,
        (int)objs[i].position.y,
        (int)objs[i].size.x,
        (int)objs[i].size.y
      };

      SDL_SetRenderDrawColor(window.getRenderer(), objs[i].color.r, objs[i].color.g, objs[i].color.b, objs[i].color.a);
      SDL_RenderDrawRect(window.getRenderer(), &rect);
 
      uniform_grid.remove(objs[i].getID());
      uniform_grid.add(objs[i]);
      uniform_grid.checkCollision(objs[i].getID());
    }

    window.flip();

    int frameTicks = SDL_GetTicks() - startTimer;
    if (frameTicks < 1000/60) {
      SDL_Delay(1000/60 - frameTicks);
    }
  }
}
