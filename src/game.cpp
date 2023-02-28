#include "game.hpp"
#include "vector2.hpp"

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

  while (true) {

    if (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        return;
        break;
      }
    }

    window.clear();

    window.flip();
  }
}
