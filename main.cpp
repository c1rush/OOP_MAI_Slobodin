#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"
#include "figure_array.h"
#include <iostream>
#include <memory>

int main() {
    FigureArray array;

    // Добавляем трапецию
    Trapezoid* trapezoid = new Trapezoid();
    std::cout << "Введите координаты 4 вершин трапеции по часовой : (x1 y1 x2 y2 x3 y3 x4 y4)" << std::endl;
    std::cin >> *trapezoid;
    array.AddFigure(trapezoid);
    std::cout << "Добавлена фигура:" << std::endl << *trapezoid << std::endl << "Area: " << double(*trapezoid) << std::endl;

    // Добавляем ромб
    Rhombus* rhombus = new Rhombus();
    std::cout << "Введите координаты 4 вершин ромба по часовой : (x1 y1 x2 y2 x3 y3 x4 y4)" << std::endl;
    std::cin >> *rhombus;
    array.AddFigure(std::move(rhombus));
    std::cout << "Добавлена фигура:" << std::endl << *rhombus << std::endl << "Area: " << double(*rhombus) << std::endl;

    // Добавляем правильный пятиугольник
    Pentagon* pentagon = new Pentagon();
    std::cout << "Введите координаты 5 вершин 5-угольника по часовой : (x1 y1 x2 y2 x3 y3 x4 y4)" << std::endl;
    std::cin >> *pentagon;
    array.AddFigure(pentagon);
    std::cout << "Добавлена фигура:" << std::endl << *pentagon << std::endl <<  "Area: " << double(*pentagon) << std::endl;

    // Вывод всех добавленных фигур
    std::cout << "Все фигуры:" << std::endl;
    array.PrintAll();

    // Вывод общей площади всех фигур
    std::cout << "Общая площадь всех фигур: " << array.TotalArea() << std::endl;

    // Удаляем фигуру по индексу 1 (удаляем ромб)
    size_t index;
    std::cout << "Введите индекс объекта для удаления:" << std::endl;
    std::cin >> index;
    std::cout << "Удаляем фигуру по индексу: " << index << std::endl;
    array.RemoveFigure(index);

    // Вывод оставшихся фигур
    std::cout << "Оставшиеся фигуры:" << std::endl;
    array.PrintAll();

    return 0;
}