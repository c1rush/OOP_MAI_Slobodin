#pragma once

#include <type_traits>
#include <iostream>
#include <limits>
#include <concepts>


namespace Shape {
    template <typename T>
    concept Scalar = std::is_scalar_v<T>;
    template <typename T>
    concept FloatingPoint = std::is_floating_point_v<T>;

    template <Scalar T>
    class Point {
    public:
        T x, y;

        Point() : x(0), y(0) {}
        Point(const T& x_, const T& y_) : x(x_), y(y_) {}

        Point(const Point<T>& point): x(point.x), y(point.y){}
        Point(Point<T>&& point) noexcept : x(std::move(point.x)), y(std::move(point.y)) {}

        ~Point() = default;      

        bool operator==(const Point& other) const {
            return (std::abs(x - other.x) <= std::numeric_limits<T>::epsilon()) && 
                   (std::abs(y - other.y) <= std::numeric_limits<T>::epsilon());
        }

        bool operator!=(const Point& other) const {
            return !(*this == other);
        }

        friend std::ostream& operator<<(std::ostream& os, const Point& point) {
            os << "(" << point.x << ", " << point.y << ")";
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Point& point) {
            is >> point.x >> point.y;
            return is;
        }
    };

}
