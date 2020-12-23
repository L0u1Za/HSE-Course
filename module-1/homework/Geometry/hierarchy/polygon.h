#pragma once
#include "shape.h"
#include <vector>

class Polygon : public Shape {
public:
    Polygon() = default;
    Polygon(std::vector<Point>& points);
    double perimeter() const override;
    double area() const override;
    bool isCongruentTo(const Shape& o) const override;
    bool isSimilarTo(const Shape& o) const override;
    bool containsPoint(Point point) const override;
    void rotate(Point center, double angle) override;
    void reflex(Line axis) override;
    void reflex(Point center) override;
    void scale(Point center, double coefficient) override;
    bool operator==(const Shape& o) const override;

    std::size_t verticesCount() const;
    const std::vector<Point>& getVertices() const;
    bool isConvex() const;
    std::vector<double> getSides() const;
    std::vector<double> getAngles() const;

  protected:
    std::vector<Point> vertex;
};