#include <iostream>
#include "include/Five.h"

int main() {
    try {
        // Проверка пустого конструктора
        Five f1;
        std::cout << "f1: " << f1 << std::endl;

        // Проверка конструктора с размером и символом
        Five f2(3, '2');
        std::cout << "f2: " << f2 << std::endl;

        // Проверка конструктора с инициализатором списка
        Five f3 = {'1', '2', '3'};
        std::cout << "f3: " << f3 << std::endl;

        // Проверка конструктора со строкой
        Five f4("123");
        std::cout << "f4: " << f4 << std::endl;

        // Проверка конструктора копирования
        Five f5(f4);
        std::cout << "f5: " << f5 << std::endl;

        // Проверка конструктора перемещения
        Five f6(std::move(f5));
        std::cout << "f6: " << f6 << std::endl;

        // Проверка оператора присваивания
        Five f7;
        f7 = f4;
        std::cout << "f7: " << f7 << std::endl;

        // Проверка оператора сложения с присваиванием
        f7 += f3;
        std::cout << "f7 += f3: " << f7 << std::endl;

        // Проверка оператора вычитания с присваиванием
        f7 -= f3;
        std::cout << "f7 -= f3: " << f7 << std::endl;

        // Проверка операторов сравнения
        std::cout << "f4 == f7: " << (f4 == f7) << std::endl;
        std::cout << "f4 < f7: " << (f4 < f7) << std::endl;
        std::cout << "f4 > f7: " << (f4 > f7) << std::endl;
        std::cout << "f4 != f7: " << (f4 != f7) << std::endl;

        // Проверка на исключения
        try {
            Five f8(0, '0');  // Генерирует исключение std::invalid_argument
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }

        try {
            Five f9("");  // Генерирует исключение std::invalid_argument
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }

        try {
            Five f10({'1', '2', '5'});  // Генерирует исключение std::invalid_argument
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}