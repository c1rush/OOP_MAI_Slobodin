#ifndef FIGURE_ARRAY_H
#define FIGURE_ARRAY_H

#include "figure.h"
#include <vector>
#include <memory>

class FigureArray {
private:
    std::vector<Figure*> figures;
public:
    void AddFigure(Figure* fig);
    void RemoveFigure(size_t index);
    double TotalArea() const;
    void PrintAll() const;
};

#endif
