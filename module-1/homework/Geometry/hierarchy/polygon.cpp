#include "polygon.h"
#include <cmath>
#include <algorithm>
Polygon::Polygon(std::vector<Point>& points) {
    for (auto &it : points) {
        vertex.push_back(it);
    }
}
double Polygon::perimeter() const {
    double P = 0.0;
    for (auto &it : getSides()) {
        P += it;
    }
    return P;
}
double Polygon::area() const {
    double S = 0.0;
    for (int i = 0; i < vertex.size(); ++i) {
        Point a = vertex[i];
        Point b = vertex[(i + 1) % int(vertex.size())];
        S += Point::vector_multiply(a, b);
    }
    return fabs(S / 2.0);
}
bool Polygon::isCongruentTo(const Shape& o) const {
    const auto* poly = dynamic_cast<const Polygon*>(&o);
    if (poly == nullptr) return false;
    if (poly->verticesCount() != verticesCount()) return false;
    bool ok = true;
    auto sides = getSides();
    auto angles = getAngles();
    auto o_sides = poly->getSides();
    auto o_angles = poly->getAngles();
    sort(sides.begin(), sides.end());
    sort(o_sides.begin(), o_sides.end());
    sort(angles.begin(), angles.end());
    sort(o_angles.begin(), o_angles.end());
    for (int i = 0; i < vertex.size(); ++i) {
        ok &= ((fabs(sides[i] - o_sides[i]) < Point::EPS) && (fabs(angles[i] - o_angles[i]) < Point::EPS));
    }
    return ok;
}
bool Polygon::isSimilarTo(const Shape& o) const {
    const auto* poly = dynamic_cast<const Polygon*>(&o);
    if (poly == nullptr) return false;
    if (poly->verticesCount() != verticesCount()) return false;
    bool ok = true;
    auto sides = getSides();
    auto angles = getAngles();
    auto o_sides = poly->getSides();
    auto o_angles = poly->getAngles();
    sort(sides.begin(), sides.end());
    sort(o_sides.begin(), o_sides.end());
    sort(angles.begin(), angles.end());
    sort(o_angles.begin(), o_angles.end());
    double k = sides.back() / o_sides.back();
    for (int i = 0; i + 1 < vertex.size(); ++i) {
        ok &= ((fabs(sides[i] / o_sides[i] - k) < Point::EPS) && (fabs(angles[i] - o_angles[i]) < Point::EPS));
    }
    return ok;
}
bool Polygon::containsPoint(Point point) const {
    double angle = 0.0;
    for (int i = 0; i < vertex.size(); ++i) {
        Point a = vertex[i];
        Point b = vertex[(i + 1) % int(vertex.size())];
        angle += Point::angle_pt_to_pt(a - point, b - point);
        if (Point::length(a - point) + Point::length(b - point) - Point::length(b - a) < Point::EPS) return true;
    }
    return (fabs(angle - 2 * Point::PI) < Point::EPS);
}
void Polygon::rotate(Point center, double angle) {
    for (auto& point : vertex) {
        Point::rotate(point, center, angle);
    }
}
void Polygon::reflex(Line axis) {
    for (auto& point : vertex) {
        Line::reflexPoint(point, axis);
    }
}
void Polygon::reflex(Point center) {
     for (auto& point : vertex) {
        Point::reflexPoint(point, center);
    }
}
void Polygon::scale(Point center, double coefficient)  {
    for (auto& point : vertex) {
        Point::scale(point, center, coefficient);
    }
}
bool Polygon::operator==(const Shape& o) const {
    const auto* poly = dynamic_cast<const Polygon*>(&o);
    if (poly == nullptr) return false;
    if (poly->verticesCount() != verticesCount()) return false;
    bool ok = true;
    auto my = vertex;
    auto other = poly->vertex;
    sort(my.begin(), my.end());
    sort(other.begin(), other.end());
    for (int i = 0; i < vertex.size(); ++i) {
        ok &= (my[i] == other[i]);
    }
    return ok;
}

std::size_t Polygon::verticesCount() const {
    return vertex.size();
}
const std::vector<Point>& Polygon::getVertices() const {
    return vertex;
}
std::vector<double> Polygon::getSides() const {
    std::vector<double> res;
    for (int i = 0; i < vertex.size(); ++i) {
        res.push_back(Point::distance_pt_to_pt(vertex[i], vertex[(i + 1) % int(vertex.size())]));
    }
    return res;
}
std::vector<double> Polygon::getAngles() const {
    std::vector<double> res;
    for (int i = 0; i < vertex.size(); ++i) {
        Point a = vertex[i];
        Point b = vertex[(i + 1) % int(vertex.size())];
        Point c = vertex[(i + 2) % int(vertex.size())];
        res.push_back(Point::angle_pt_to_pt(a - b, c - b));
    }
    return res;
}

bool Polygon::isConvex() const {
    if (vertex.size() < 3) return false;
    Point a = vertex[0];
    Point b = vertex[1];
    Point c = vertex[2];
    bool sign = Point::vector_multiply((b - a) , (c - b)) < Point::EPS;
    for (int i = 1; i < vertex.size(); i++) {
        a = vertex[i % vertex.size()];
        b = vertex[(i + 1) % vertex.size()];
        c = vertex[(i + 2) % vertex.size()];

        if (((Point::vector_multiply((b - a) , (c - b))) < Point::EPS) != sign) {
            return false;
        }
    }
    return true;
}
