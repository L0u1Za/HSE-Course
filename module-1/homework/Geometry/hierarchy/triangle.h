#pragma once
#include "circle.h"
#include "polygon.h"

class Triangle : public Polygon {
public:
    Triangle(Point a, Point b, Point c);
    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
    Point getOuter() const;
    Point getInner() const;
private:
    Point a, b, c;
};