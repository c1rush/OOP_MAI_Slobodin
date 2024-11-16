#pragma once

#include <memory>
#include <functional>
#include "CustomIterator.h"

namespace CustomContainers {

    template <class T, class Allocator = std::pmr::polymorphic_allocator<T>>
    class CustomQueue {
    private:
        struct Node {
            T data;
            Node* next;

            Node(const T& value) : data(value), next(nullptr) {}
            Node(T&& value) : data(std::move(value)), next(nullptr) {}
        };

        using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
        using NodeAllocatorTraits = std::allocator_traits<NodeAllocator>;

        Node* front_ptr;
        Node* back_ptr;
        std::size_t queue_size;
        NodeAllocator allocator;

    public:
        using iterator = CustomIterator<T, CustomQueue<T, Allocator>>;
        using const_iterator = CustomIterator<const T, const CustomQueue<T, Allocator>>;

        explicit CustomQueue(const Allocator& alloc = Allocator()) 
            : front_ptr(nullptr), back_ptr(nullptr), queue_size(0), allocator(alloc) {}

        CustomQueue(const CustomQueue& other) 
            : front_ptr(nullptr), back_ptr(nullptr), queue_size(0), allocator(NodeAllocatorTraits::select_on_container_copy_construction(other.allocator)) {
            Node* current = other.front_ptr;
            while(current) {
                enqueue(current->data);
                current = current->next;
            }
        }

        CustomQueue(CustomQueue&& other) noexcept 
            : front_ptr(other.front_ptr), back_ptr(other.back_ptr), queue_size(other.queue_size), allocator(std::move(other.allocator)) {
            other.front_ptr = nullptr;
            other.back_ptr = nullptr;
            other.queue_size = 0;
        }

        CustomQueue& operator=(const CustomQueue& other) {
            if(this != &other){
                clear();
                if(NodeAllocatorTraits::propagate_on_container_copy_assignment::value) {
                    NodeAllocatorTraits::destroy(allocator, &allocator);
                    NodeAllocatorTraits::construct(allocator, &allocator, other.allocator);
                }
                Node* current = other.front_ptr;
                while(current) {
                    enqueue(current->data);
                    current = current->next;
                }
            }
            return *this;
        }


        CustomQueue& operator=(CustomQueue&& other) noexcept {
            if(this != &other){
                clear();
                if(NodeAllocatorTraits::propagate_on_container_move_assignment::value) {
                    allocator = std::move(other.allocator);
                }
                front_ptr = other.front_ptr;
                back_ptr = other.back_ptr;
                queue_size = other.queue_size;

                other.front_ptr = nullptr;
                other.back_ptr = nullptr;
                other.queue_size = 0;
            }
            return *this;
        }

        ~CustomQueue() {
            clear();
        }

        void enqueue(const T& item) {
            Node* new_node = NodeAllocatorTraits::allocate(allocator, 1);
            try {
                NodeAllocatorTraits::construct(allocator, new_node, item);
            } catch(...) {
                NodeAllocatorTraits::deallocate(allocator, new_node, 1);
                throw;
            }

            if(back_ptr) {
                back_ptr->next = new_node;
                back_ptr = new_node;
            } else {
                front_ptr = back_ptr = new_node;
            }
            ++queue_size;
        }

        void enqueue(T&& item) {
            Node* new_node = NodeAllocatorTraits::allocate(allocator, 1);
            try {
                NodeAllocatorTraits::construct(allocator, new_node, std::move(item));
            } catch(...) {
                NodeAllocatorTraits::deallocate(allocator, new_node, 1);
                throw;
            }

            if(back_ptr) {
                back_ptr->next = new_node;
                back_ptr = new_node;
            } else {
                front_ptr = back_ptr = new_node;
            }
            ++queue_size;
        }

        void dequeue() {
            if(empty()) {
                throw std::out_of_range("Dequeue from empty queue.");
            }
            Node* old_front = front_ptr;
            front_ptr = front_ptr->next;
            if(!front_ptr) {
                back_ptr = nullptr;
            }
            NodeAllocatorTraits::destroy(allocator, old_front);
            NodeAllocatorTraits::deallocate(allocator, old_front, 1);
            --queue_size;
        }

        T& front() {
            if(empty()) {
                throw std::out_of_range("Accessing front of empty queue.");
            }
            return front_ptr->data;
        }

        const T& front() const {
            if(empty()) {
                throw std::out_of_range("Accessing front of empty queue.");
            }
            return front_ptr->data;
        }

        bool empty() const {
            return queue_size == 0;
        }

        std::size_t get_size() const {
            return queue_size;
        }

        void clear() {
            while(!empty()) {
                dequeue();
            }
        }

        // Итераторы
        iterator begin() {
            return iterator(this, 0);
        }

        iterator end() {
            return iterator(this, queue_size);
        }

        const_iterator begin() const {
            return const_iterator(this, 0);
        }

        const_iterator end() const {
            return const_iterator(this, queue_size);
        }

        // Доступ к элементам по индексу (для итератора)
        T& at(std::size_t idx) {
            if(idx >= queue_size) {
                throw std::out_of_range("Index out of range.");
            }
            Node* current = front_ptr;
            for(std::size_t i = 0; i < idx; ++i) {
                current = current->next;
            }
            return current->data;
        }

        const T& at(std::size_t idx) const {
            if(idx >= queue_size) {
                throw std::out_of_range("Index out of range.");
            }
            Node* current = front_ptr;
            for(std::size_t i = 0; i < idx; ++i) {
                current = current->next;
            }
            return current->data;
        }
    };

}
