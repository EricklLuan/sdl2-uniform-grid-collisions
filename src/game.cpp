#include "game.hpp"
#include "vector2.hpp"
#include "uniformGrid.hpp"

#include <iostream>

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

  UniformGrid uniform_grid = UniformGrid(Vector2(128, 128), 10);

  std::vector<Rect> rects;

  for (int i = 0; i < 100; i++){
    rects.push_back(Rect{});
  }
  

  Uint32 last=0;

  while (true) {
    Uint32 startTimer = SDL_GetTicks();

    if (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        return;
        break;
      }
    }


    for (int i = 0; i < rects.size(); i++) {
      uniform_grid.removeRect(rects[i]);
      rects[i].rect.x += (int)rects[i].velocity.x + 1;
      rects[i].rect.y += (int)rects[i].velocity.y + 1;

      if (rects[i].rect.x > 128) {
        rects[i].rect.x = -rects[i].rect.w;
      } else if (rects[i].rect.x + rects[i].rect.w < 0) {
        rects[i].rect.x = 128;
      }

      if (rects[i].rect.y > 128) {
        rects[i].rect.y = -rects[i].rect.h;
      } else if (rects[i].rect.y + rects[i].rect.h < 0) {
        rects[i].rect.y = 128;
      }

      uniform_grid.addRect(rects[i]);
    }

    window.clear();
    for (int i = 0; i < rects.size(); i++) {
      uniform_grid.checkCollision(rects[i]);
      
      if (rects[i].isColliding == true) {
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 255, 0, 255);
      } else {
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
      }

      SDL_RenderDrawRect(window.getRenderer(), &rects[i].rect);
    }
    window.flip();

    int frameTicks = SDL_GetTicks() - startTimer;
    if (frameTicks < 1000/60) {
      SDL_Delay(1000/60 - frameTicks);
    }
  }
}
