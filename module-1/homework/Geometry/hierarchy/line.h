#pragma once
#include "point.h"

struct Line {
    double a, b, c;
    Line() = default;
    Line(Point a, Point b);
    Line(double _a, double _b, double _c);
    void normalize();
    bool operator==(const Line& o) const;
    bool operator!=(const Line& o) const;
    static double distance_pt_to_line(const Point& p, const Line& l);
    static Point projection_pt_to_line(const Point& p, const Line& l);
    static void reflexPoint(Point& point, Line l);
};