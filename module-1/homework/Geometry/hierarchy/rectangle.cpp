#include "rectangle.h"
#include <cmath>

Rectangle::Rectangle(Point top, Point bot, double k) : top(top), bot(bot), k(k) {
    double diag = Point::distance_pt_to_pt(top, bot);
    height = diag / sqrt(1 + k * k);
    width = sqrt(diag * diag - height * height);

    Point topLeft = top - Point(width, 0);
    Point botLeft = top - Point(0, height);

    vertex = {top, topLeft, bot, botLeft};
    O = (top + bot) * 0.5;
}

Point Rectangle::center() const {
    return O;
}

std::pair<Line, Line> Rectangle::diagonals() const {
    Line a = {top, bot};
    Line b = {a.a, -a.b, a.c};
    return {a, b};
}

double Rectangle::getHeight() const {
    return height;
}

double Rectangle::getWidth() const {
    return width;
}