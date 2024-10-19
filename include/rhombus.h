#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"

class Rhombus : public Figure {
private:
    std::pair<double, double> a, b, c, d;
public:
    Rhombus();
    Rhombus(const std::pair<double, double>& a, const std::pair<double, double>& b, 
            const std::pair<double, double>& c, const std::pair<double, double>& d);

    std::pair<double, double> Center() const override;

    operator double() const override;

    friend std::ostream& operator<<(std::ostream& os, const Rhombus& rhombus);
    friend std::istream& operator>>(std::istream& is, Rhombus& rhombus);


    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) noexcept override;
    bool operator==(const Figure& other) const override;

};

#endif
