#include "ellipse.h"
#include <cmath>

Ellipse::Ellipse(Point fa, Point fb, double radius) : fa(fa), fb(fb), a(radius / 2) {
    c = Point::distance_pt_to_pt(fa, fb) / 2.0;
    b = sqrt(a * a - c * c);
}

double Ellipse::perimeter() const {
    return 4 * (Point::PI * a * b + (a - b)) / (a + b);
}

double Ellipse::area() const {
    return Point::PI * a * b;
}

std::pair<Point, Point> Ellipse::focuses() const {
    return {fa, fb};
}

double Ellipse::eccentricity() const {
    return Ellipse::c / a;
}

Point Ellipse::center() const {
    return (fa + fb) * 0.5;
}

bool Ellipse::isCongruentTo(const Shape& o) const {
    const auto* ellipse = dynamic_cast<const Ellipse*>(&o);
    if (ellipse == nullptr) return false;
    return (fabs(Point::distance_pt_to_pt(fa, fb) - Point::distance_pt_to_pt(ellipse->fa, ellipse->fb)) < Point::EPS) && (fabs(a - ellipse->a) < Point::EPS);
}

bool Ellipse::isSimilarTo(const Shape& o) const {
    const auto* ellipse = dynamic_cast<const Ellipse*>(&o);
    if (ellipse == nullptr) return false;
    double k = Point::distance_pt_to_pt(fa, fb) / Point::distance_pt_to_pt(ellipse->fa, ellipse->fb);
    return fabs(a - ellipse->a * k) < Point::EPS;
}

bool Ellipse::containsPoint(Point point) const {
    return (Point::distance_pt_to_pt(fa, point) + Point::distance_pt_to_pt(fb, point)) <= 2 * a;
}

void Ellipse::rotate(Point center, double angle) {
    Point::rotate(fa, center, angle);
    Point::rotate(fb, center, angle);
}

void Ellipse::reflex(Line axis) {
    Line::reflexPoint(fa, axis);
    Line::reflexPoint(fb, axis);
}
void Ellipse::reflex(Point center) {
    Point::reflexPoint(fa, center);
    Point::reflexPoint(fb, center);
}

void Ellipse::scale(Point center, double coefficient) {
    Point::scale(fa, center, coefficient);
    Point::scale(fb, center, coefficient);
}

std::pair<Line, Line> Ellipse::directries() const {
    auto k = b * b / a;
    auto com = k / (eccentricity() * (1 - eccentricity() * eccentricity()));
    return {{1, 0, com}, {1, 0, -com}};
}

bool Ellipse::operator==(const Shape& o) const {
    const auto* ellipse = dynamic_cast<const Ellipse*>(&o);
    if (ellipse == nullptr) return false;
    return ((fa == ellipse->fa && fb == ellipse->fb) || (fa == ellipse->fb && fb == ellipse->fa)) && fabs(a - ellipse->a) < Point::EPS;
}