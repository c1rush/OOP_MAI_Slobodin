#include <iostream>
#include <memory>
#include "src/array.h"
#include "src/pentagon.h"
#include "src/rhombus.h"
#include "src/trapezoid.h"

using namespace Shape;

int main() {
    Array<std::shared_ptr<IFigure>> figures;

    while (true) {
        std::cout << "Выберите действие:\n"
                  << "1. Добавить фигуру\n"
                  << "2. Показать все фигуры\n"
                  << "3. Вычислить общую площадь\n"
                  << "4. Удалить фигуру по индексу\n"
                  << "5. Выйти\n"
                  << "Введите номер действия: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Выберите тип фигуры:\n"
                      << "1. Пятиугольник\n"
                      << "2. Ромб\n"
                      << "3. Трапеция\n"
                      << "Введите номер типа: ";
            int type;
            std::cin >> type;

            std::shared_ptr<IFigure> figure;

            if (type == 1) {
                std::shared_ptr<Pentagon<double>> pentagon = std::make_shared<Pentagon<double>>();
                std::cin >> *pentagon;
                figure = pentagon;
            }
            else if (type == 2) {
                std::shared_ptr<Rhombus<double>> rhombus = std::make_shared<Rhombus<double>>();
                std::cin >> *rhombus;
                figure = rhombus;
            }
            else if (type == 3) {

                std::shared_ptr<Trapezoid<double>> trapezoid = std::make_shared<Trapezoid<double>>();
                std::cin >> *trapezoid;
                figure = trapezoid;
            }
            else {
                std::cout << "Некорректный тип фигуры.\n";
                continue;
            }

            figures.push_back(figure);
            std::cout << "Фигура добавлена.\n";
        }
        else if (choice == 2) {
            std::cout << "Все фигуры:\n";
            figures.PrintAll();
        }
        else if (choice == 3) {
            double total_area = figures.TotalArea();
            std::cout << "Общая площадь всех фигур: " << total_area << "\n";
        }
        else if (choice == 4) {
            std::cout << "Введите индекс фигуры для удаления: ";
            size_t index;
            std::cin >> index;
            try {
                figures.remove_at(index);
                std::cout << "Фигура удалена.\n";
            }
            catch (const std::out_of_range& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
        }
        else if (choice == 5) {
            std::cout << "Выход из программы.\n";
            break;
        }
        else {
            std::cout << "Некорректный выбор.\n";
        }
    }

    return 0;
}
