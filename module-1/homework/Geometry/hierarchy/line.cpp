#include "line.h"
#include <cmath>

Line::Line(Point a, Point b) {
    this->a = (a.y - b.y);
    this->b = (b.x - a.x);
    this->c = Point::vector_multiply(a, b);
    normalize();
}
Line::Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {
    normalize();
}
void Line::normalize() {
    double n = sqrt(a * a + b * b);
    a /= n;
    b /= n;
    c /= n;
}

bool Line::operator==(const Line& o) const {
    return (a - o.a < Point::EPS) && (b - o.b < Point::EPS) && (c - o.c < Point::EPS);
}
bool Line::operator!=(const Line& o) const {
    return !(*this == o);
}
double Line::distance_pt_to_line(const Point& p, const Line& l) {
    return (l.a * p.x + l.b * p.y + l.c);
}
Point Line::projection_pt_to_line(const Point& p, const Line& l) {
    double d = distance_pt_to_line(p, l);
	Point n = { l.a, l.b };
	n.x *= d;
	n.y *= d;
	return (p - n);
}
void Line::reflexPoint(Point& point, Line l) {
    Point center = Line::projection_pt_to_line(point, l);
    Point::reflexPoint(point, center);
}