#pragma once

#include <memory_resource>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <cstdint> 

namespace CustomContainers {

    struct MemoryBlock {
        void* ptr;
        std::size_t size;
        bool is_free;

        MemoryBlock(void* p, std::size_t s, bool free = true) : ptr(p), size(s), is_free(free) {}
    };

    class FixedBlockMemoryResource : public std::pmr::memory_resource {
    private:
        std::vector<MemoryBlock> blocks;
        std::size_t total_size;
        void* memory_pool;

    protected:
        virtual void* do_allocate(std::size_t bytes, std::size_t alignment) override {
            // Проверка выравнивания
            if ((alignment & (alignment - 1)) != 0 || alignment == 0) {
                throw std::invalid_argument("Alignment must be a non-zero power of two.");
            }

            for(std::size_t i = 0; i < blocks.size(); ++i) {
                if(blocks[i].is_free && blocks[i].size >= bytes) {
                    // Вычисляем выровненный адрес
                    uintptr_t current_address = reinterpret_cast<uintptr_t>(blocks[i].ptr);
                    uintptr_t aligned_address = (current_address + alignment - 1) & ~(alignment - 1);
                    std::size_t padding = aligned_address - current_address;

                    if(blocks[i].size < bytes + padding) {
                        continue; // Не хватает места после выравнивания
                    }

                    if(padding > 0) {
                        // Создаём блок для отступа
                        blocks.emplace(blocks.begin() + i, blocks[i].ptr, padding, true);
                        // Обновляем текущий блок
                        blocks[i + 1].ptr = reinterpret_cast<void*>(aligned_address);
                        blocks[i + 1].size -= padding;
                        i++; // Переходим к новому блоку
                    }

                    if(blocks[i].size > bytes) {
                        // Создаём оставшийся свободный блок
                        blocks.emplace(blocks.begin() + i + 1, 
                                      reinterpret_cast<void*>(aligned_address + bytes), 
                                      blocks[i].size - bytes, 
                                      true);
                        blocks[i].size = bytes;
                    }

                    blocks[i].is_free = false;

                    return blocks[i].ptr;
                }
            }
            throw std::bad_alloc();
        }

        virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
            for(std::size_t i = 0; i < blocks.size(); ++i) {
                if(blocks[i].ptr == p) {
                    if(blocks[i].is_free) {
                        throw std::logic_error("Double deallocation detected.");
                    }
                    blocks[i].is_free = true;

                    // Пытаемся объеденить с предыдущим
                    if(i > 0 && blocks[i - 1].is_free) {
                        blocks[i - 1].size += blocks[i].size;
                        blocks.erase(blocks.begin() + i);
                        i--;
                    }

                    // Пытаемся объеденить со следующим
                    if(i + 1 < blocks.size() && blocks[i + 1].is_free) {
                        blocks[i].size += blocks[i + 1].size;
                        blocks.erase(blocks.begin() + i + 1);
                    }

                    return;
                }
            }

            throw std::invalid_argument("Pointer does not belong to this memory resource.");
        }

        virtual bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
            return this == &other;
        }

    public:
        FixedBlockMemoryResource(std::size_t size) : total_size(size) {
            memory_pool = std::malloc(total_size);
            if(!memory_pool) {
                throw std::bad_alloc();
            }
            blocks.emplace_back(memory_pool, total_size, true);

            blocks.reserve(100);
        }

        ~FixedBlockMemoryResource() {
            std::free(memory_pool);
        }

        std::size_t get_total_size() const {
            return total_size;
        }

        std::size_t get_used_memory() const {
            std::size_t used = 0;
            for(const auto &block : blocks) {
                if(!block.is_free) {
                    used += block.size;
                }
            }
            return used;
        }

        std::size_t get_free_memory() const {
            std::size_t free_mem = 0;
            for(const auto &block : blocks) {
                if(block.is_free) {
                    free_mem += block.size;
                }
            }
            return free_mem;
        }

        const std::vector<MemoryBlock>& get_blocks() const {
            return blocks;
        }
    };

}
