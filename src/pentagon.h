#pragma once
#include "figure.h"
#include <cmath>

namespace Shape {

template <typename T>
class Pentagon : public Figure<T, 5> {
public:
    using Figure<T, 5>::vertices;

    Pentagon() : Figure<T, 5>({{0,0},{1,1},{2,1},{2,-1},{1,-1}}) {}

    Pentagon(std::initializer_list<Point<T>> points) : Figure<T, 5>(points) {}

    Pentagon(const Point<T>& center, T radius) requires FloatingPoint<T> {
        double pi = std::acos(-1);
        for (size_t i = 0; i < 5; ++i) {
            double angle = i * 2 * pi / 5;
            vertices[i] = Point<T>(center.x + radius * std::cos(angle),
                                   center.y + radius * std::sin(angle));
        }
    }

    Pentagon(const Pentagon& other) : Figure<T, 5>(other) {}
    Pentagon(Pentagon&& other) noexcept : Figure<T, 5>(std::move(other)) {}

    Pentagon& operator=(const Pentagon& other) {
        if (this != &other) {
            Figure<T, 5>::operator=(other);
        }
        return *this;
    }

    Pentagon& operator=(Pentagon&& other) noexcept {
        if (this != &other) {
            Figure<T, 5>::operator=(std::move(other));
        }
        return *this;
    }

    bool operator==(const Pentagon& other) const {
        for (size_t i = 0; i < 5; ++i) {
            if (*this->vertices[i] != *other.vertices[i]) {
                return false;
            }
        }
        return true;
    }

    friend std::istream& operator>>(std::istream& is, Pentagon& pentagon) {
        std::cout << "Enter 5 points for the pentagon:\n";
        for (auto& vertex : pentagon.vertices) {
            T x, y;
            is >> x >> y;
            vertex = std::make_unique<Point<T>>(x, y);
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pentagon& pentagon) {
        os << "Pentagon with vertices:\n";
        for (const auto& vertex : pentagon.vertices) {
            os << *vertex << " ";
        }
        return os;
    }
};

}
