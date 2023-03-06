#include "game.hpp"
#include "vector2.hpp"
#include "uniformGrid.hpp"

#include <iostream>
#include <vector>
#include <memory>

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

  std::vector<std::unique_ptr<Object> > objs;

  objs.push_back(std::make_unique<Object>(Vector2((float)(rand() % (128 - 20)), (float)(rand() % (128 - 20))), Vector2(20, 20)));
  uniform_grid.add(*objs.back());

  while (true) {
    Uint32 startTimer = SDL_GetTicks();

    if (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        return;
        break;
      case SDL_KEYDOWN:
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_LEFT) {
          objs.push_back(std::make_unique<Object>(Vector2(e.button.x - 10, e.button.y - 10), Vector2(20, 20)));
          uniform_grid.add(*objs.back());
        }
        break;
      }
    }

    window.clear();
   
    for (int i = 0; i < objs.size(); i++) {

      objs[i]->position += objs[i]->velocity;

      if (objs[i]->position.x < (0 - objs[i]->size.x)) {
        objs[i]->position.x = window.vSize.x;
      } else if (objs[i]->position.x > window.vSize.x) {
        objs[i]->position.x = 0 - objs[i]->size.x;
      }

      if (objs[i]->position.y < (0 - objs[i]->size.y)) {
        objs[i]->position.y = window.vSize.y;
      } else if (objs[i]->position.y > window.vSize.y) {
        objs[i]->position.y = 0 - objs[i]->size.x;
      } 

      SDL_Rect rect = {
        (int)objs[i]->position.x,
        (int)objs[i]->position.y,
        (int)objs[i]->size.x,
        (int)objs[i]->size.y
      };

      SDL_SetRenderDrawColor(window.getRenderer(), objs[i]->color.r, objs[i]->color.g, objs[i]->color.b, objs[i]->color.a);
      SDL_RenderDrawRect(window.getRenderer(), &rect);
 
      uniform_grid.update(objs[i]->getID());
      uniform_grid.checkCollision(objs[i]->getID());
    }

    window.flip();

    int frameTicks = SDL_GetTicks() - startTimer;
    if (frameTicks < 1000/60) {
      SDL_Delay(1000/60 - frameTicks);
    }
  }
}
