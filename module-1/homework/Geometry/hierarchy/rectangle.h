#pragma once
#include "polygon.h"

class Rectangle : public Polygon {
public:
    Rectangle(Point top, Point bot, double k);
    Point center() const;
    std::pair<Line, Line> diagonals() const;
    double getHeight() const;
    double getWidth() const;
protected:
    Point O;
private:
    Point top, bot;
    double k;
};