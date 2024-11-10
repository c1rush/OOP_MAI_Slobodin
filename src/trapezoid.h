#pragma once
#include "figure.h"

namespace Shape {

template <typename T>
class Trapezoid : public Figure<T, 4> {
private:
    using Figure<T, 4>::vertices;
public:
    Trapezoid() : Figure<T, 4>({{0,0}, {1,1}, {2,1}, {2,0}}) {}

    Trapezoid(std::initializer_list<Point<T>> points) : Figure<T, 4>(points) {}

    // Конструктор с двумя базами и высотой (по дефолту прямоугольник)
    Trapezoid(const Point<T>& p1, const Point<T>& p2, T height) {
        vertices[0] = std::make_unique<Point<T>>(p1.x, p1.y);
        vertices[1] = std::make_unique<Point<T>>(p2.x, p2.y);
        vertices[2] = std::make_unique<Point<T>>(p2.x, p2.y + height);
        vertices[3] = std::make_unique<Point<T>>(p1.x, p1.y + height);
    }

    Trapezoid(const Trapezoid& other) : Figure<T, 4>(other) {}
    Trapezoid(Trapezoid&& other) noexcept : Figure<T, 4>(std::move(other)) {}

    Trapezoid& operator=(const Trapezoid& other) {
        if (this != &other) {
            Figure<T, 4>::operator=(other);
        }
        return *this;
    }

    Trapezoid& operator=(Trapezoid&& other) noexcept {
        if (this != &other) {
            Figure<T, 4>::operator=(std::move(other));
        }
        return *this;
    }

    bool operator==(const Trapezoid& other) const {
        for (size_t i = 0; i < 4; ++i) {
            if (*this->vertices[i] != *other.vertices[i]) {
                return false;
            }
        }
        return true;
    }

    friend std::istream& operator>>(std::istream& is, Trapezoid& trapezoid) {
        std::cout << "Enter 4 points for the trapezoid:\n";
        for (auto& vertex : trapezoid.vertices) {
            T x, y;
            is >> x >> y;
            vertex = std::make_unique<Point<T>>(x, y);
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Trapezoid& trapezoid) {
        os << "Trapezoid with vertices:\n";
        for (const auto& vertex : trapezoid.vertices) {
            os << *vertex << " ";
        }
        return os;
    }
};

}
