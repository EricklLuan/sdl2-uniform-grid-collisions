#pragma once

class Vector2 {
public:
  float x, y;

  Vector2(float nX=0.0f, float nY=0.0f);
  
  Vector2 operator+(Vector2 response);
  Vector2 operator-(Vector2 response);
  Vector2 operator*(Vector2 response);
  Vector2 operator/(Vector2 response); 
};
