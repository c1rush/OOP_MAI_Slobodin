#pragma once
#include "figure.h"

namespace Shape {

template <typename T>
class Rhombus : public Figure<T, 4> {
private:
    using Figure<T, 4>::vertices;
public:
    Rhombus() : Figure<T, 4>({{-1,0}, {0,1}, {1,0}, {0,-1}}) {}

    Rhombus(std::initializer_list<Point<T>> points) : Figure<T, 4>(points) {}

    // Конструктор с диагоналями и центром
    Rhombus(const Point<T>& center, T d1, T d2) requires FloatingPoint<T> {
        vertices[0] = std::make_unique<Point<T>>(center.x + d1 / 2, center.y);
        vertices[1] = std::make_unique<Point<T>>(center.x, center.y + d2 / 2);
        vertices[2] = std::make_unique<Point<T>>(center.x - d1 / 2, center.y);
        vertices[3] = std::make_unique<Point<T>>(center.x, center.y - d2 / 2);
    }

    Rhombus(const Rhombus& other) : Figure<T, 4>(other) {}
    Rhombus(Rhombus&& other) noexcept : Figure<T, 4>(std::move(other)) {}

    Rhombus& operator=(const Rhombus& other) {
        if (this != &other) {
            Figure<T, 4>::operator=(other);
        }
        return *this;
    }

    Rhombus& operator=(Rhombus&& other) noexcept {
        if (this != &other) {
            Figure<T, 4>::operator=(std::move(other));
        }
        return *this;
    }

    bool operator==(const Rhombus& other) const {
        for (size_t i = 0; i < 4; ++i) {
            if (*this->vertices[i] != *other.vertices[i]) {
                return false;
            }
        }
        return true;
    }

    friend std::istream& operator>>(std::istream& is, Rhombus& rhombus) {
        std::cout << "Enter 4 points for the rhombus:\n";
        for (auto& vertex : rhombus.vertices) {
            T x, y;
            is >> x >> y;
            vertex = std::make_unique<Point<T>>(x, y);
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Rhombus& rhombus) {
        os << "Rhombus with vertices:\n";
        for (const auto& vertex : rhombus.vertices) {
            os << *vertex << " ";
        }
        return os;
    }
};

}
