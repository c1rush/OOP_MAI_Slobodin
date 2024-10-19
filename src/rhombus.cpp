#include "rhombus.h"
#include <cmath>
#include <vector>

Rhombus::Rhombus() : a{0, 0}, b{0, 0}, c{0, 0}, d{0, 0} {}

Rhombus::Rhombus(const std::pair<double, double>& a, const std::pair<double, double>& b, 
                 const std::pair<double, double>& c, const std::pair<double, double>& d)
    : a(a), b(b), c(c), d(d) {}

std::pair<double, double> Rhombus::Center() const {
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

Rhombus::operator double() const {
    return 0.5 * std::abs(
        a.first * b.second + b.first * c.second + c.first * d.second + d.first * a.second - 
        (a.second * b.first + b.second * c.first + c.second * d.first + d.second * a.first)
    );
}

std::ostream& operator<<(std::ostream& os, const Rhombus& rhombus) {
    os << "Rhombus: (" << rhombus.a.first << ", " << rhombus.a.second << "), ("
       << rhombus.b.first << ", " << rhombus.b.second << "), ("
       << rhombus.c.first << ", " << rhombus.c.second << "), ("
       << rhombus.d.first << ", " << rhombus.d.second << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Rhombus& rhombus) {
    is >> rhombus.a.first >> rhombus.a.second
       >> rhombus.b.first >> rhombus.b.second
       >> rhombus.c.first >> rhombus.c.second
       >> rhombus.d.first >> rhombus.d.second;
    return is;
}

Figure& Rhombus::operator=(const Figure& other) {
    if (this != &other) {
        if(const Rhombus* rhomb = dynamic_cast<const Rhombus*>(&other)){        
            a = rhomb->a;
            b = rhomb->b;
            c = rhomb->c;
            d = rhomb->d;
        }
    }
    return *this;
}

Figure& Rhombus::operator=(Figure&& other) noexcept {
    if (this != &other) {
        if(const Rhombus* rhomb = dynamic_cast<Rhombus*>(&other)){
            a = std::move(rhomb->a);
            b = std::move(rhomb->b);
            c = std::move(rhomb->c);
            d = std::move(rhomb->d);
        }
    }
    return *this;
}

bool Rhombus::operator==(const Figure& other) const {
    const Rhombus* otherRhombus = dynamic_cast<const Rhombus*>(&other);
    return otherRhombus && (a == otherRhombus->a) && (b == otherRhombus->b)
        && (c == otherRhombus->c) && (d == otherRhombus->d);
}
