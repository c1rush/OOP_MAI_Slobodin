#include "rhombus.h"
#include <cmath>
#include <vector>

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

Rhombus::Rhombus(const Rhombus& other) : vertices(other.vertices) {}

Rhombus::Rhombus(Rhombus&& other) noexcept : vertices(std::move(other.vertices)) {}

Rhombus::Rhombus() : vertices{{{0, 0}, {0, 0}, {0, 0}, {0, 0}}} {}

Rhombus::Rhombus(const std::pair<double, double>& a, const std::pair<double, double>& b, 
                 const std::pair<double, double>& c, const std::pair<double, double>& d)
    : vertices({a, b, c, d}) {}

std::pair<double, double> Rhombus::Center() const {
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
        vertices[0].first * vertices[1].second + vertices[1].first * vertices[2].second +
        vertices[2].first * vertices[3].second + vertices[3].first * vertices[0].second -
        (vertices[0].second * vertices[1].first + vertices[1].second * vertices[2].first +
         vertices[2].second * vertices[3].first + vertices[3].second * vertices[0].first)
    );
}

void Rhombus::print(std::ostream& os) const {
    os << "Rhombus: (" << vertices[0].first << ", " << vertices[0].second << "), ("
       << vertices[1].first << ", " << vertices[1].second << "), ("
       << vertices[2].first << ", " << vertices[2].second << "), ("
       << vertices[3].first << ", " << vertices[3].second << ")";
}

void Rhombus::read(std::istream& is) {
    is >> vertices[0].first >> vertices[0].second
       >> vertices[1].first >> vertices[1].second
       >> vertices[2].first >> vertices[2].second
       >> vertices[3].first >> vertices[3].second;
}

Figure& Rhombus::operator=(const Figure& other) {
    if (this != &other) {
        if (const Rhombus* rhomb = dynamic_cast<const Rhombus*>(&other)) {
            vertices = rhomb->vertices;
        }
    }
    return *this;
}

Figure& Rhombus::operator=(Figure&& other) noexcept {
    if (this != &other) {
        if (const Rhombus* rhomb = dynamic_cast<Rhombus*>(&other)) {
            vertices = std::move(rhomb->vertices);
        }
    }
    return *this;
}

bool Rhombus::operator==(const Figure& other) const {
    const Rhombus* otherRhombus = dynamic_cast<const Rhombus*>(&other);
    return otherRhombus && (vertices == otherRhombus->vertices);
}
