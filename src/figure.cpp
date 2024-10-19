#include "figure.h"

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    os << "Figure: [Area: " << static_cast<double>(fig) << ", Center: (" 
       << fig.Center().first << ", " << fig.Center().second << ")]";
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig){}