#include "figure_array.h"

void FigureArray::AddFigure(Figure* fig) {
    figures.push_back(std::move(fig));
}

void FigureArray::RemoveFigure(size_t index) {
    if (index < figures.size()) {
        figures.erase(figures.begin() + index);
    } else {
        std::cerr << "Invalid index" << std::endl;
    }
}

double FigureArray::TotalArea() const {
    double totalArea = 0;
    for (const auto& fig : figures) {
        totalArea += double(*fig);
    }
    return totalArea;
}

void FigureArray::PrintAll() const {
    for (const Figure* fig : figures) {
        if(fig){
            std::cout << "Figure info:" << std::endl;
            std::cout << "Center: (" << fig->Center().first << ", " << fig->Center().second << ")" << std::endl;
            std::cout << "Area: " << double(*fig) << std::endl;
        }
    }
}
