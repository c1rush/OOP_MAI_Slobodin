#include "../include/trapezoid.h"
#include <cmath>
#include <vector>

Trapezoid::Trapezoid() : a{0, 0}, b{0, 0}, c{0, 0}, d{0, 0} {}

Trapezoid::Trapezoid(const std::pair<double, double>& a, const std::pair<double, double>& b, 
                     const std::pair<double, double>& c, const std::pair<double, double>& d)
    : a(a), b(b), c(c), d(d) {}

std::pair<double, double> Trapezoid::Center() const {
    std::vector<std::pair<double, double>> vertices = {a, b, c, d, a};
    double A = 0;
    double C_x = 0, C_y = 0;


    for (size_t i = 0; i < 4; ++i) {
        double xi = vertices[i].first;
        double yi = vertices[i].second;
        double xi1 = vertices[i + 1].first;
        double yi1 = vertices[i + 1].second;
        double cross = xi * yi1 - xi1 * yi;
        A += cross;
        C_x += (xi + xi1) * cross;
        C_y += (yi + yi1) * cross;
    }

    A = A / 2.0;
    C_x = C_x / (6.0 * A);
    C_y = C_y / (6.0 * A);
    if (std::abs(C_x) < 1e-4) C_x = 0.0;
    if (std::abs(C_y) < 1e-4) C_y = 0.0;

    return {C_x, C_y};
}

Trapezoid::operator double() const {
    return 0.5 * std::abs(
        a.first * b.second + b.first * c.second + c.first * d.second + d.first * a.second - 
        (a.second * b.first + b.second * c.first + c.second * d.first + d.second * a.first)
    );
}

std::ostream& operator<<(std::ostream& os, const Trapezoid& trapezoid) {
    os << "Trapezoid: (" << trapezoid.a.first << ", " << trapezoid.a.second << "), ("
       << trapezoid.b.first << ", " << trapezoid.b.second << "), ("
       << trapezoid.c.first << ", " << trapezoid.c.second << "), ("
       << trapezoid.d.first << ", " << trapezoid.d.second << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Trapezoid& trapezoid) {
    is >> trapezoid.a.first >> trapezoid.a.second
       >> trapezoid.b.first >> trapezoid.b.second
       >> trapezoid.c.first >> trapezoid.c.second
       >> trapezoid.d.first >> trapezoid.d.second;
    return is;
}

Figure& Trapezoid::operator=(const Figure& other) {
    if (this != &other) {
        if (const Trapezoid* trap = dynamic_cast<const Trapezoid*>(&other)) {
            a = trap->a;
            b = trap->b;
            c = trap->c;
            d = trap->d;
        }
    }
    return *this;
}

Figure& Trapezoid::operator=(Figure&& other) noexcept {
    if (this != &other) {
        if (Trapezoid* trap = dynamic_cast<Trapezoid*>(&other)) {
            a = std::move(trap->a);
            b = std::move(trap->b);
            c = std::move(trap->c);
            d = std::move(trap->d);
        }
    }
    return *this;
}

bool Trapezoid::operator==(const Figure& other) const {
    const Trapezoid* otherTrapezoid = dynamic_cast<const Trapezoid*>(&other);
    return otherTrapezoid && (a == otherTrapezoid->a) && (b == otherTrapezoid->b)
        && (c == otherTrapezoid->c) && (d == otherTrapezoid->d);
}
