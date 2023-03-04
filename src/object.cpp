#include "object.hpp"

int Object::mCouter=0;

Object::Object(Vector2 nPosition, Vector2 nSize): position(nPosition), size(nSize) {
  mId=++mCouter;
}

int Object::getID() {
  return mId;
}
