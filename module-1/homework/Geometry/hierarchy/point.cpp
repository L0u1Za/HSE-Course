#include "point.h"
#include <cmath>


Point::Point(double _x, double _y) : x(_x), y(_y) {}
Point::Point(const Point& o) {
    this->x = o.x;
    this->y = o.y;
}
bool Point::operator==(const Point& o) const {
    return (fabs(this->x - o.x) < Point::EPS) && (fabs(this->y - o.y) < Point::EPS);
}
bool Point::operator!=(const Point& o) const {
    return !(*this == o);
}
Point Point::operator*(double value) const {
    return {x * value, y * value};
}
Point Point::operator+(const Point& o) const {
    return {x + o.x, y + o.y};
}
Point& Point::operator+=(const Point& o) {
    this->x += o.x;
    this->y += o.y;
    return *this;
}
Point Point::operator-(const Point& o) const {
    return {x - o.x, y - o.y};
}
Point& Point::operator-=(const Point& o) {
    this->x -= o.x;
    this->y -= o.y;
    return *this;
}
bool Point::operator<(const Point& o) const {
  return x != o.x ? x < o.x : y < o.y;
}
double Point::length(Point a) {
    return sqrt(a.x * a.x + a.y * a.y);
}
double Point::distance_pt_to_pt(Point a, Point b) {
    return length(a - b);
}
double Point::vector_multiply(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}
double Point::scalar_multiply(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}
double Point::angle_pt_to_pt(const Point& a, const Point& b) {
    return atan2(Point::vector_multiply(a, b) , Point::scalar_multiply(a, b));
}

void Point::scale(Point& point, Point center, double coefficient) {
    point = center + (point - center) * coefficient;
}
void Point::rotate(Point& point, Point center, double angle) {
    angle = angle / 180.0 * Point::PI;
    Point del = point - center;
    Point mid = {del.x * cos(angle) - del.y * sin(angle), del.x * sin(angle) + del.y * cos(angle)};
    point = mid + center;
}
void Point::reflexPoint(Point& point, Point o) {
    point = {2 * o.x - point.x, 2 * o.y - point.y};
}
void Point::normalize() {
    double len = Point::length(*this);
    x /= len;
    y /= len;
}