#include "vector2.hpp"

Vector2 Vector2::operator+(Vector2 response) {
  Vector2 result;
  result.x = this->x + response.x;
  result.y = this->y + response.y;
  return result;
}

Vector2 Vector2::operator-(Vector2 response) {
  Vector2 result;
  result.x = this->x - response.x;
  result.y = this->y - response.y;
  return result;
}

Vector2 Vector2::operator/(Vector2 response) {
  Vector2 result;
  result.x = this->x / response.x;
  result.y = this->y / response.y;
  return result;
}

void Vector2::operator+=(Vector2 response) {
  this->x += response.x;
  this->y += response.y;
}

Vector2 Vector2::operator*(Vector2 response) {
  Vector2 result;
  result.x = this->x * response.x;
  result.y = this->y * response.y;
  return result;
}

Vector2::Vector2(float nX, float nY): x(nX), y(nY) {
  
}
