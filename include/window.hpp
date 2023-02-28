#pragma once

#include "vector2.hpp"

#include <SDL2/SDL.h>

class Window {
private:
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;

  const char* mTitle;
public:
  const Vector2 wSize;
  const Vector2 vSize;

  Window(const char* title, Vector2 windowSize, Vector2 viewportSize);
  ~Window();

  bool init();

  void clear();
  void flip();

  SDL_Window* getWindow();
  SDL_Renderer* getRenderer();
};