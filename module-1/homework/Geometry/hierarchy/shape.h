#pragma once
#include "point.h"
#include "line.h"
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool isCongruentTo(const Shape& o) const = 0;
    virtual bool isSimilarTo(const Shape& o) const = 0;
    virtual bool containsPoint(Point point) const = 0;
    virtual void rotate(Point center, double angle) = 0;
    virtual void reflex(Line axis) = 0;
    virtual void reflex(Point center) = 0;
    virtual void scale(Point center, double coefficient) = 0;
    virtual bool operator==(const Shape& o) const = 0;
};