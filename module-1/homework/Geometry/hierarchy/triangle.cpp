#include "triangle.h"
#include <cmath>

Triangle::Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {
    vertex = {a, b, c};
}
Point Triangle::getOuter() const {
	Point n1 = { a.y - b.y, b.x - a.x };
	Point n2 = { b.y - c.y, c.x - b.x };

	Point v1 = { -n1.y, n1.x };
	Point v2 = { -n2.y, n2.x };

	double x0 = (b.x + a.x) / 2;
	double y0 = (b.y + a.y) / 2;

	double x1 = (c.x + b.x) / 2;
	double y1 = (c.y + b.y) / 2;

	Line l1 = { v1.x, v1.y, -v1.x * x0 - v1.y * y0 };
	Line l2 = { v2.x, v2.y, -v2.x * x1 - v2.y * y1 };

	Point per;
	if (!(fabs(l1.a * l2.b - l2.a * l1.b) < Point::EPS)) {
		per = { (l2.c * l1.b - l1.c* l2.b) / (l1.a * l2.b - l2.a * l1.b), (l1.c * l2.a - l2.c * l1.a) / (l1.a * l2.b - l2.a * l1.b) };
	} else {
		throw std::exception();
	}
	return per;
}

Circle Triangle::circumscribedCircle() const {
    Point center = getOuter();
    return Circle(center, Point::length(a - center));
}
Point Triangle::getInner() const {
	Point x = a, y = b, z = c;
	x.normalize(); y.normalize(), z.normalize();
	Point v1 = x + y;
	Point v2 = y + z;
	Line l1 = { v1.x, v1.y, -v1.x * a.x - v1.y * a.y };
	Line l2 = { v2.x, v2.y, -v2.x * b.x - v2.y * b.y };

	Point per;
	if (!(fabs(l1.a * l2.b - l2.a * l1.b) < Point::EPS)) {
		per = { (l2.c * l1.b - l1.c* l2.b) / (l1.a * l2.b - l2.a * l1.b), (l1.c * l2.a - l2.c * l1.a) / (l1.a * l2.b - l2.a * l1.b) };
	} else {
		throw std::exception();
	}
	return per;
}
Circle Triangle::inscribedCircle() const {
    return Circle(getInner(), area() / perimeter());
}

