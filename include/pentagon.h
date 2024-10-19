#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.h"

class Pentagon : public Figure {
private:
    std::pair<double, double> a, b, c, d, e;
public:
    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;
    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;

    Pentagon();
    Pentagon(const std::pair<double, double>& a, const std::pair<double, double>& b, 
             const std::pair<double, double>& c, const std::pair<double, double>& d, 
             const std::pair<double, double>& e);

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
