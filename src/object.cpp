#include "object.hpp"

int Object::mCouter=0;

Object::Object(Vector2 nPosition, Vector2 nSize): position(nPosition), size(nSize) {
  mId=++mCouter;
  velocity = Vector2((float)(rand() % 2 + 1), (float)(rand() % 2 + 1));
}

int Object::getID() {
  return mId;
}
