#define SDL_MAIN_HANDLED

#include "game.hpp"

int main(int, char**) {
  Game game = Game();
  game.run();
}
