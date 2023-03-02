#include "uniformGrid.hpp"

#include <cmath>
#include <algorithm>
#include <iostream>

UniformGrid::UniformGrid(Vector2 viewportSize, int nCellSize): cellSize(nCellSize) {
  int width = std::floor(viewportSize.x / cellSize) + 2;
  int height = std::floor(viewportSize.y / cellSize) + 2;

  for (int y = -2; y <= height + 1; y++) {
    std::vector<std::vector<Rect*> > row = {};
    for (int x = -2; x <= width + 1; x++) {
      row.push_back(std::vector<Rect*>{});
    }
    grid.push_back(row);
  }
}

UniformGrid::~UniformGrid() {
  
}

void UniformGrid::addRect(Rect &rect) {
  int startX = std::floor((rect.rect.x) / (cellSize)) + 2;
  int endX = std::floor((rect.rect.x + rect.rect.w) / (cellSize)) + 2;
  int startY = std::floor((rect.rect.y) / (cellSize)) + 2;
  int endY = std::floor((rect.rect.y + rect.rect.h) / (cellSize)) + 2;

  for (int y = startY; y <= endY; y++) {
    std::vector<std::vector<Rect*>> &row = grid[y];
    for (int x = startX; x <= endX; x++) {
      std::vector<Rect*> &column = row[x];
      if (std::find(column.begin(), column.end(), &rect) == column.end()) {
        column.push_back(&rect);
      }
    }
  }
}

void UniformGrid::removeRect(Rect &rect) {
  rect.isColliding = false;
  int startX = std::floor((rect.rect.x) / (cellSize)) + 2;
  int endX = std::floor((rect.rect.x + rect.rect.w) / (cellSize)) + 2;
  int startY = std::floor((rect.rect.y) / (cellSize)) + 2;
  int endY = std::floor((rect.rect.y + rect.rect.h) / (cellSize)) + 2;

  for (int y = startY; y <= endY; y++) {
    std::vector<std::vector<Rect*>> &row = grid[y];
    for (int x = startX; x <= endX; x++) {
      std::vector<Rect*> &column = row[x];
      if (auto item = find(column.begin(), column.end(), &rect); item != column.end()) {
        column.erase(column.begin() + (item - column.begin()));
      }
    }
  }
}

std::vector<Rect*> UniformGrid::getCollisions(Rect &rect) {
  int startX = std::floor((rect.rect.x) / (cellSize)) + 2;
  int endX = std::floor((rect.rect.x + rect.rect.w) / (cellSize)) + 2;
  int startY = std::floor((rect.rect.y) / (cellSize)) + 2;
  int endY = std::floor((rect.rect.y + rect.rect.h) / (cellSize)) + 2;

  std::vector<Rect*> collisions;

  for (int y = startY; y <= endY; y++) {
    std::vector<std::vector<Rect*>> &row = grid[y];
    for (int x = startX; x <= endX; x++) {
      std::vector<Rect*> &column = row[x];
      for (int z = 0; z < column.size(); z++) {
        Rect* obj = column[z];
        if (obj == &rect) {
          continue;
        }

        if (collide(*obj, rect)) {
          collisions.push_back(obj);
        }
      }
    }
  }

  return collisions;
}

void UniformGrid::checkCollision(Rect &rect) {
  std::vector<Rect*> collisions = getCollisions(rect);

  if (!collisions.size() > 0) return; 

  rect.isColliding = true;
  for (int i = 0; i < collisions.size(); i++) {
    collisions[i]->isColliding = true;
  }
}

bool UniformGrid::collide(Rect &a, Rect &b) {
  return a.rect.x < b.rect.x + b.rect.w &&
           a.rect.x + a.rect.w > b.rect.x &&
           a.rect.y < b.rect.y + b.rect.h &&
           a.rect.h + a.rect.y > b.rect.y;
}
