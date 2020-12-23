#pragma once
#include "point.h"

class Shape;
class Polygon;
class Triangle;
class Rectangle;
class Line {
    friend Shape;
    friend Polygon;
    friend Triangle;
    friend Rectangle;
public:
    Line() = default;
    Line(Point a, Point b);
    Line(double _a, double _b, double _c);
    void normalize();
    bool operator==(const Line& o) const;
    bool operator!=(const Line& o) const;
    static double distance_pt_to_line(const Point& p, const Line& l);
    static Point projection_pt_to_line(const Point& p, const Line& l);
    static void reflexPoint(Point& point, Line l);
private:
    double a, b, c;
};