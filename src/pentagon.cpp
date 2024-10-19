#include "pentagon.h"
#include <cmath>
#include <vector>

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        a = other.a;
        b = other.b;
        c = other.c;
        d = other.d;
        e = other.e;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        a = std::move(other.a);
        b = std::move(other.b);
        c = std::move(other.c);
        d = std::move(other.d);
        e = std::move(other.e);
    }
    return *this;
}

Pentagon::Pentagon(const Pentagon& other){
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    e = other.e;
}

Pentagon::Pentagon(Pentagon&& other) noexcept {
    a = std::move(other.a);
    b = std::move(other.b);
    c = std::move(other.c);
    d = std::move(other.d);
    e = std::move(other.e);
}


Pentagon::Pentagon() : a{0, 0}, b{0, 0}, c{0, 0}, d{0, 0}, e{0, 0} {}

Pentagon::Pentagon(const std::pair<double, double>& a, const std::pair<double, double>& b, 
                   const std::pair<double, double>& c, const std::pair<double, double>& d, 
                   const std::pair<double, double>& e)
    : a(a), b(b), c(c), d(d), e(e) {}

std::pair<double, double> Pentagon::Center() const {
    std::vector<std::pair<double, double>> vertices = {a, b, c, d, e, a};
    double A = 0;
    double C_x = 0, C_y = 0;


    for (size_t i = 0; i < 5; ++i) {
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

Pentagon::operator double() const {
    return 0.5 * std::abs(
        a.first * b.second + b.first * c.second + c.first * d.second +
        d.first * e.second + e.first * a.second - 
        (a.second * b.first + b.second * c.first + c.second * d.first +
        d.second * e.first + e.second * a.first)
    );
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon: (" << a.first << ", " << a.second << "), ("
       << b.first << ", " << b.second << "), ("
       << c.first << ", " << c.second << "), ("
       << d.first << ", " << d.second << "), ("
       << e.first << ", " << e.second << ")";
}

void Pentagon::read(std::istream& is) {
    is >> a.first >> a.second
       >> b.first >> b.second
       >> c.first >> c.second
       >> d.first >> d.second
       >> e.first >> e.second;

}

Figure& Pentagon::operator=(const Figure& other) {
    if (this != &other) {
        if(const Pentagon* pent = dynamic_cast<const Pentagon*>(&other)){
            a = pent->a;
            b = pent->b;
            c = pent->c;
            d = pent->d;
            e = pent->e;
        }
    }
    return *this;
}

Figure& Pentagon::operator=(Figure&& other) noexcept {
    if (this != &other) {
        if(const Pentagon* pent = dynamic_cast<Pentagon*>(&other)){
            a = std::move(pent->a);
            b = std::move(pent->b);
            c = std::move(pent->c);
            d = std::move(pent->d);
            e = std::move(pent->e);
        }
    }
    return *this;
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&other);
    return otherPentagon && (a == otherPentagon->a) && (b == otherPentagon->b)
        && (c == otherPentagon->c) && (d == otherPentagon->d) && (e == otherPentagon->e);
}
