#pragma once

class Point {
public:
    double x, y;
    
    Point() = default;
    Point(double x, double y);
    Point(const Point& o);
    bool operator==(const Point& o) const;
    bool operator!=(const Point& o) const;
    Point operator*(double value) const;
    Point operator+(const Point& o) const;
    Point& operator+=(const Point& o);
    Point operator-(const Point& o) const;
    Point& operator-=(const Point& o);
    void normalize();
    bool operator<(const Point& o) const;
    static double length(Point a);
    static double distance_pt_to_pt(Point a, Point b);
    static void scale(Point& point, Point center, double coefficient);
    static void rotate(Point& point, Point center, double angle);
    static void reflexPoint(Point& point, Point o);
    static double vector_multiply(const Point& a, const Point& b);
    static double scalar_multiply(const Point& a, const Point& b);
    static double angle_pt_to_pt(const Point& a, const Point& b);
    static constexpr double PI = 3.1415926;
    static constexpr double EPS = 1e-5;
};