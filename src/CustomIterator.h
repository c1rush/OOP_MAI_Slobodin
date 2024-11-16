#pragma once

#include <iterator>
#include <stdexcept>

namespace CustomContainers {

    template<class ItemT, class QueueT>
    class CustomIterator {
    private:
        QueueT* queue;
        std::size_t index;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type = ItemT;
        using reference = ItemT&;
        using pointer = ItemT*;
        using iterator_category = std::forward_iterator_tag;

        CustomIterator(QueueT* q, std::size_t idx) : queue(q), index(idx) {}

        reference operator*() const {
            if(index >= queue->get_size()) {
                throw std::out_of_range("Iterator is out of range.");
            }
            return queue->at(index);
        }

        pointer operator->() const {
            if(index >= queue->get_size()) {
                throw std::out_of_range("Iterator is out of range.");
            }
            return &(queue->at(index));
        }

        CustomIterator& operator++() {
            if(index < queue->get_size()) {
                ++index;
            }
            return *this;
        }

        CustomIterator operator++(int) {
            CustomIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator!=(const CustomIterator& other) const {
            return (queue != other.queue) || (index != other.index);
        }

        bool operator==(const CustomIterator& other) const {
            return !(*this != other);
        }
    };

}
