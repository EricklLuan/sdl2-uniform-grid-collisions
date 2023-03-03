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

  UniformGrid uniform_grid = UniformGrid(Vector2(10, 10), window.vSize);

  std::vector<Object> objects = {
    Object{Vector2(rand() % 100, rand() % 100), Vector2(20, 20)},
    Object{Vector2(rand() % 100, rand() % 100), Vector2(20, 20)},
    Object{Vector2(rand() % 100, rand() % 100), Vector2(20, 20)},
    Object{Vector2(rand() % 100, rand() % 100), Vector2(20, 20)},
  };

  for (Object &a: objects) {
    uniform_grid.add(a);
  }

  while (true) {
    Uint32 startTimer = SDL_GetTicks();

    if (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        return;
        break;
      case SDL_KEYDOWN:
        if (e.key.repeat == 0) {
          if (e.key.keysym.scancode == SDL_SCANCODE_D) objects[0].position.x += 1;
          if (e.key.keysym.scancode == SDL_SCANCODE_A) objects[0].position.x -= 1;
          if (e.key.keysym.scancode == SDL_SCANCODE_W) objects[0].position.y -= 1;
          if (e.key.keysym.scancode == SDL_SCANCODE_S) objects[0].position.y += 1;
        }
      }
    }

    window.clear();
   
    for (int i = 0; i < objects.size(); i++) {
      SDL_Rect rect = {
        (int)objects[i].position.x,
        (int)objects[i].position.y,
        (int)objects[i].size.x,
        (int)objects[i].size.y,
      };

      SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
      SDL_RenderDrawRect(window.getRenderer(), &rect);

      uniform_grid.update(objects[i].id);
    }
    uniform_grid.checkCollision(objects[0].id);

    window.flip();

    int frameTicks = SDL_GetTicks() - startTimer;
    if (frameTicks < 1000/60) {
      SDL_Delay(1000/60 - frameTicks);
    }
  }
}
