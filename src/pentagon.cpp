#include "pentagon.h"
#include <cmath>
#include <vector>

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

Pentagon::Pentagon(const Pentagon& other) : vertices(other.vertices) {}

Pentagon::Pentagon(Pentagon&& other) noexcept : vertices(std::move(other.vertices)) {}


Pentagon::Pentagon() : vertices{{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}} {}

Pentagon::Pentagon(const std::pair<double, double>& a, const std::pair<double, double>& b, 
                   const std::pair<double, double>& c, const std::pair<double, double>& d, 
                   const std::pair<double, double>& e)
    : vertices({a, b, c, d, e}) {}

std::pair<double, double> Pentagon::Center() const {
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
        vertices[0].first * vertices[1].second + vertices[1].first * vertices[2].second + vertices[2].first * vertices[3].second +
        vertices[3].first * vertices[4].second + vertices[4].first * vertices[0].second - 
        (vertices[0].second * vertices[1].first + vertices[1].second * vertices[2].first + vertices[2].second * vertices[3].first +
        vertices[3].second * vertices[4].first + vertices[4].second * vertices[0].first)
    );
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon: (" << vertices[0].first << ", " << vertices[0].second << "), ("
       << vertices[1].first << ", " << vertices[1].second << "), ("
       << vertices[2].first << ", " << vertices[2].second << "), ("
       << vertices[3].first << ", " << vertices[3].second << "), ("
       << vertices[4].first << ", " << vertices[4].second << ")";
}

void Pentagon::read(std::istream& is) {
    is >> vertices[0].first >> vertices[0].second
       >> vertices[1].first >> vertices[1].second
       >> vertices[2].first >> vertices[2].second
       >> vertices[3].first >> vertices[3].second
       >> vertices[4].first >> vertices[4].second;

}

Figure& Pentagon::operator=(const Figure& other) {
    if (this != &other) {
        if(const Pentagon* pent = dynamic_cast<const Pentagon*>(&other)){
            vertices = pent->vertices;
        }
    }
    return *this;
}

Figure& Pentagon::operator=(Figure&& other) noexcept {
    if (this != &other) {
        if(const Pentagon* pent = dynamic_cast<Pentagon*>(&other)){
            vertices = std::move(pent->vertices);
        }
    }
    return *this;
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&other);
    return otherPentagon && (vertices == otherPentagon->vertices);
}
