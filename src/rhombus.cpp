#include "rhombus.h"
#include <cmath>
#include <vector>

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        a = other.a;
        b = other.b;
        c = other.c;
        d = other.d;
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        a = std::move(other.a);
        b = std::move(other.b);
        c = std::move(other.c);
        d = std::move(other.d);
    }
    return *this;
}

Rhombus::Rhombus(const Rhombus& other){
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
}

Rhombus::Rhombus(Rhombus&& other) noexcept {
    a = std::move(other.a);
    b = std::move(other.b);
    c = std::move(other.c);
    d = std::move(other.d);
}

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

void Rhombus::print(std::ostream& os) const {
    os << "Rhombus: (" << a.first << ", " << a.second << "), ("
       << b.first << ", " << b.second << "), ("
       << c.first << ", " << c.second << "), ("
       << d.first << ", " << d.second << ")";
}

void Rhombus::read(std::istream& is) {
    is >> a.first >> a.second
       >> b.first >> b.second
       >> c.first >> c.second
       >> d.first >> d.second;
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
