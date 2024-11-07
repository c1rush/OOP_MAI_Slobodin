#pragma once

#include <memory>
#include "point.h"

namespace Shape {

// Интерфейсный класс IFigure
class IFigure {
public:
    virtual ~IFigure() = default;

    virtual explicit operator double() const = 0;

    virtual void print(std::ostream& os) const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const IFigure& figure) {
    figure.print(os);
    return os;
}

}
