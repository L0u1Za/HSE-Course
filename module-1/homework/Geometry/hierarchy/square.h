#pragma once
#include "rectangle.h"
#include "circle.h"

class Square : public Rectangle {
public:
    Square(Point top, Point bot);
    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
};