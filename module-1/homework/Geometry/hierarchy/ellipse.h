#pragma once
#include "polygon.h"

class Ellipse : public Shape {
public:
    Ellipse(Point a, Point b, double radius);
    double perimeter() const override;
    double area() const override;
    bool isCongruentTo(const Shape& o) const override;
    bool isSimilarTo(const Shape& o) const override;
    bool containsPoint(Point point) const override;
    void rotate(Point center, double angle) override;
    void reflex(Line axis) override;
    void reflex(Point center) override;
    void scale(Point center, double coefficient) override;
    std::pair<Point, Point> focuses() const;
    std::pair<Line, Line> directries() const;
    double eccentricity() const;
    Point center() const;
    bool operator==(const Shape& o) const override;

private:
    Point fa, fb;
    double a, b, c;

};