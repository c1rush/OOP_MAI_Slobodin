#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"

class Trapezoid : public Figure {
private:
    std::pair<double, double> a, b, c, d;
public:
    Trapezoid();
    Trapezoid(const std::pair<double, double>& a, const std::pair<double, double>& b, 
              const std::pair<double, double>& c, const std::pair<double, double>& d);

    std::pair<double, double> Center() const override;
    
    operator double() const override;

    friend std::ostream& operator<<(std::ostream& os, const Trapezoid& trapezoid);
    friend std::istream& operator>>(std::istream& is, Trapezoid& Trapezoid);


    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
};

#endif
