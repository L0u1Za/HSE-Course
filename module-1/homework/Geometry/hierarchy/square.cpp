#include "square.h"
#include <cmath>

Square::Square(Point top, Point bot) : Rectangle(top, bot, 1) {}

Circle Square::circumscribedCircle() const {
  return {O, getHeight() * sqrt(2) / 2.0};
}

Circle Square::inscribedCircle() const {
  return {O, getHeight() / 2};
}