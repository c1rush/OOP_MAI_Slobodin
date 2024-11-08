#pragma once

#include <array>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include "point.h"
#include "ifigure.h"

namespace Shape {

template <typename T, size_t PntCnt>
class Figure : public IFigure {
protected:
    std::array<std::unique_ptr<Point<T>>, PntCnt> vertices;

public:
    Figure() {
        for (size_t i = 0; i < PntCnt; ++i) {
            vertices[i] = std::make_unique<Point<T>>(0, i * i);
        }
    }

    Figure(std::initializer_list<Point<T>> points) {
        if (points.size() != PntCnt) {
            throw std::invalid_argument("Incorrect number of points provided");
        }

        auto it = points.begin();
        for (size_t i = 0; i < PntCnt; ++i, ++it) {
            vertices[i] = std::make_unique<Point<T>>(it->x, it->y);
        }
    }

    Figure(const Figure<T, PntCnt>& other) {
        for (size_t i = 0; i < PntCnt; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    Figure(Figure<T, PntCnt>&& other) noexcept : vertices(std::move(other.vertices)) {}

    Figure& operator=(const Figure<T, PntCnt>& other) {
        if (this != &other) {
            for (size_t i = 0; i < PntCnt; ++i) {
                vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
            }
        }
        return *this;
    }

    Figure& operator=(Figure<T, PntCnt>&& other) noexcept {
        if (this != &other) {
            vertices = std::move(other.vertices);
        }
        return *this;
    }

    // Формула шнурка общая для всех фигур
    virtual std::unique_ptr<Point<T>> Center() const {
        T A = 0, C_x = 0, C_y = 0;
        if(PntCnt < 2) { return std::make_unique<Point<T>>(vertices[0]->x, vertices[0]->y); }
        for (size_t i = 0; i < PntCnt; ++i) {
            T xi = vertices[i]->x;
            T yi = vertices[i]->y;
            T xi1 = vertices[(i + 1) % PntCnt]->x;
            T yi1 = vertices[(i + 1) % PntCnt]->y;
            T cross = xi * yi1 - xi1 * yi;
            A += cross;
            C_x += (xi + xi1) * cross;
            C_y += (yi + yi1) * cross;
        }
        A = A / 2.0;

        if (A == 0) {
            throw std::runtime_error("Cannot calculate center for a degenerate figure with zero area.");
        }

        C_x = C_x / (6.0 * A);
        C_y = C_y / (6.0 * A);
        return std::make_unique<Point<T>>(C_x, C_y);
    }

    virtual explicit operator double() const override {
        double area = 0;
        if (PntCnt < 3) { return 0; }
        for (size_t i = 0; i < PntCnt; ++i) {
            size_t j = (i + 1) % PntCnt;
            area += static_cast<double>(vertices[i]->x) * static_cast<double>(vertices[j]->y) -
                    static_cast<double>(vertices[j]->x) * static_cast<double>(vertices[i]->y);
        }
        return 0.5 * std::abs(area);
    }

    virtual bool operator==(const Figure<T, PntCnt>& other) const {
        for (size_t i = 0; i < PntCnt; ++i) {
            if (!(*vertices[i] == *other.vertices[i])) {
                return false;
            }
        }
        return true;
    }

    void print(std::ostream& os) const override {
        os << "Figure with " << PntCnt << " vertices:\n";
        for (const auto& vertex : vertices) {
            os << *vertex << " ";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T, PntCnt>& fig) {
        fig.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T, PntCnt>& fig) {
        std::cout << "Enter coordinates for " << PntCnt << " points:\n";
        for (auto& vertex : fig.vertices) {
            T x, y;
            is >> x >> y;
            vertex = std::make_unique<Point<T>>(x, y); 
        }
        return is;
    }

    virtual ~Figure() = default;

};

}
