#include "circle.h"

Circle::Circle(Point center, double radius) 
    : Ellipse::Ellipse(center, center, radius * 2), R(radius) {}

double Circle::radius() const {
    return R;
}