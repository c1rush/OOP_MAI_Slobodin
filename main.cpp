#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"
#include "figure_array.h"
#include <iostream>
#include <memory>

int main() {
    FigureArray array;

    // Добавление нескольких фигур с фиксированными координатами
    // Добавляем трапецию
    Figure* trapezoid = new Trapezoid({0, 0}, {1, 1}, {2, 1}, {2, 0});
    array.AddFigure(std::move(trapezoid));

    // Добавляем ромб
    Figure* rhombus = new Rhombus({0, 0}, {1, 1}, {2, 0}, {1, -1});
    array.AddFigure(std::move(rhombus));

    // Добавляем правильный пятиугольник
    Figure* pentagon = new Pentagon({1, 0}, {0.309, 0.951}, {-0.809, 0.588}, 
                                    {-0.809, -0.588}, {0.309, -0.951});
    array.AddFigure(std::move(pentagon));

    // Вывод всех добавленных фигур
    std::cout << "Все фигуры:" << std::endl;
    array.PrintAll();

    // Вывод общей площади всех фигур
    std::cout << "Общая площадь всех фигур: " << array.TotalArea() << std::endl;

    // Удаляем фигуру по индексу 1 (удаляем ромб)
    size_t index = 1;
    std::cout << "Удаляем фигуру по индексу: " << index << std::endl;
    array.RemoveFigure(index);

    // Вывод оставшихся фигур
    std::cout << "Оставшиеся фигуры:" << std::endl;
    array.PrintAll();

    return 0;
}