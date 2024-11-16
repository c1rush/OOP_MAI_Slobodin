#include "src/CustomMemoryResource.h"
#include "src/CustomQueue.h"
#include <iostream>
#include <string>

struct ComplexType {
    int id;
    std::string name;
    double value;

    bool operator==(const ComplexType& other) const {
        return id == other.id && name == other.name && value == other.value;
    }
};

int main() {
    try {
        // Инициализация пользовательского ресурса памяти с размером 1024 байт
        CustomContainers::FixedBlockMemoryResource customResource(1024);

        // Создание аллокатора для int и ComplexType
        std::pmr::polymorphic_allocator<int> intAllocator(&customResource);
        std::pmr::polymorphic_allocator<ComplexType> complexAllocator(&customResource);

        // Создание очереди для int
        CustomContainers::CustomQueue<int, std::pmr::polymorphic_allocator<int>> intQueue(intAllocator);
        intQueue.enqueue(10);
        intQueue.enqueue(20);
        intQueue.enqueue(30);

        std::cout << "Int Queue: ";
        for(auto val : intQueue){
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // Создание очереди для ComplexType
        CustomContainers::CustomQueue<ComplexType, std::pmr::polymorphic_allocator<ComplexType>> complexQueue(complexAllocator);
        complexQueue.enqueue(ComplexType{1, "Alpha", 100.5});
        complexQueue.enqueue(ComplexType{2, "Beta", 200.75});
        complexQueue.enqueue(ComplexType{3, "Gamma", 300.25});

        std::cout << "Complex Queue:" << std::endl;
        for(auto &item : complexQueue){
            std::cout << "ID: " << item.id << ", Name: " << item.name << ", Value: " << item.value << std::endl;
        }

        // Демонстрация работы dequeue
        std::cout << "\nAfter dequeuing an element from intQueue:" << std::endl;
        intQueue.dequeue();
        for(auto val : intQueue){
            std::cout << val << " ";
        }
        std::cout << std::endl;

    } catch(const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
