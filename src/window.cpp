#include "window.hpp"

#include <iostream>
Window::Window(const char* title, Vector2 windowSize, Vector2 viewportSize)
: mTitle(title), wSize(windowSize), vSize(viewportSize) {
  
}

Window::~Window() {
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

bool Window::init() {
  mWindow = SDL_CreateWindow(mTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wSize.x, wSize.y, SDL_WINDOW_OPENGL);
  if (mWindow == nullptr) {
    std::cout << "Failed to create the window: " << SDL_GetError() << "\n";
    return false;
  }

  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
  if (mRenderer == nullptr) {
    std::cout << "Failed to create the renderer: " << SDL_GetError() << "\n";
    return false;
  }

  SDL_RenderSetLogicalSize(mRenderer, vSize.x, vSize.y);

  return true;
}

void Window::clear() {
  SDL_RenderClear(mRenderer);
}

void Window::flip() {
  SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
  SDL_RenderPresent(mRenderer);
}

SDL_Window* Window::getWindow() {
  return mWindow;
}

SDL_Renderer* Window::getRenderer() {
  return mRenderer;
}
