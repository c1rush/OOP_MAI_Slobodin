#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"

class Rhombus : public Figure {
private:
    std::pair<double, double> a, b, c, d;
public:
    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) noexcept;
    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;

    Rhombus();
    Rhombus(const std::pair<double, double>& a, const std::pair<double, double>& b, 
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
