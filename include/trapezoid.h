#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"

class Trapezoid : public Figure {
private:
    std::pair<double, double> a, b, c, d;
public:
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    Trapezoid();
    Trapezoid(const std::pair<double, double>& a, const std::pair<double, double>& b, 
              const std::pair<double, double>& c, const std::pair<double, double>& d);

    std::pair<double, double> Center() const override;
    
    operator double() const override;

    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
protected:
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};

#endif
