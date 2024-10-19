#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.h"

class Pentagon : public Figure {
private:
    std::pair<double, double> a, b, c, d, e;
public:
    Pentagon();
    Pentagon(const std::pair<double, double>& a, const std::pair<double, double>& b, 
             const std::pair<double, double>& c, const std::pair<double, double>& d, 
             const std::pair<double, double>& e);

    std::pair<double, double> Center() const override;

    operator double() const override;

    friend std::ostream& operator<<(std::ostream& os, const Pentagon& pentagon);
    friend std::istream& operator>>(std::istream& is, Pentagon& pentagon);

    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;
};

#endif
