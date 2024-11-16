#include <gtest/gtest.h>
#include "../src/CustomQueue.h"
#include "../src/CustomMemoryResource.h"
#include <string>

struct ComplexType {
    int id;
    std::string name;
    double value;

    bool operator==(const ComplexType& other) const {
        return id == other.id && name == other.name && value == other.value;
    }
};

namespace CustomContainers {

    template<class T>
    bool compare_queues(const CustomQueue<T, std::pmr::polymorphic_allocator<T>>& q1, const std::vector<T>& q2){
        if(q1.get_size() != q2.size()) return false;
        std::size_t idx = 0;
        for(auto &item : q1){
            if(!(item == q2[idx])) return false;
            ++idx;
        }
        return true;
    }

    TEST(QueueTests, ShouldEnqueueElementsCorrectly) {
        FixedBlockMemoryResource customResource(1024);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);

        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);

        std::vector<int> expected = {1, 2, 3};
        EXPECT_TRUE(compare_queues(queue, expected));
    }

    TEST(QueueTests, ShouldDequeueElementsCorrectly) {
        FixedBlockMemoryResource customResource(1024);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);

        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);
        queue.dequeue();

        std::vector<int> expected = {20, 30};
        EXPECT_TRUE(compare_queues(queue, expected));
    }

    TEST(QueueTests, ShouldHandleComplexTypesCorrectly) {
        FixedBlockMemoryResource customResource(2048);
        std::pmr::polymorphic_allocator<ComplexType> allocator(&customResource);
        CustomQueue<ComplexType, std::pmr::polymorphic_allocator<ComplexType>> queue(allocator);

        queue.enqueue(ComplexType{1, "Node1", 100.0});
        queue.enqueue(ComplexType{2, "Node2", 200.0});
        queue.enqueue(ComplexType{3, "Node3", 300.0});

        std::vector<ComplexType> expected = {
            {1, "Node1", 100.0},
            {2, "Node2", 200.0},
            {3, "Node3", 300.0}
        };

        EXPECT_TRUE(compare_queues(queue, expected));
    }

    TEST(AllocatorTests, ShouldTrackMemoryCorrectly) {
        FixedBlockMemoryResource customResource(1024);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);

        EXPECT_EQ(customResource.get_used_memory(), 0);

        queue.enqueue(5);
        EXPECT_GT(customResource.get_used_memory(), 0);

        queue.enqueue(10);
        EXPECT_GT(customResource.get_used_memory(), 0);

        queue.dequeue();
        EXPECT_GT(customResource.get_free_memory(), 0);
    }

    TEST(QueueTests, ShouldThrowWhenDequeuingEmptyQueue) {
        FixedBlockMemoryResource customResource(1024);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);

        EXPECT_THROW(queue.dequeue(), std::out_of_range);
    }

    TEST(QueueTests, ShouldThrowWhenAccessingFrontOfEmptyQueue) {
        FixedBlockMemoryResource customResource(1024);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);

        EXPECT_THROW(queue.front(), std::out_of_range);
    }

    TEST(QueueTests, CopyConstructorCreatesIndependentQueue) {
        FixedBlockMemoryResource customResource(2048);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> originalQueue(allocator);
        
        originalQueue.enqueue(100);
        originalQueue.enqueue(200);
        originalQueue.enqueue(300);
        
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> copiedQueue(originalQueue);
        
        std::vector<int> expected = {100, 200, 300};
        EXPECT_TRUE(compare_queues(copiedQueue, expected));
        
        originalQueue.dequeue();
        std::vector<int> expectedOriginal = {200, 300};
        EXPECT_TRUE(compare_queues(originalQueue, expectedOriginal));
        EXPECT_TRUE(compare_queues(copiedQueue, expected));
    }

    TEST(QueueTests, MoveConstructorTransfersOwnership) {
        FixedBlockMemoryResource customResource(2048);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> originalQueue(allocator);
        
        originalQueue.enqueue(10);
        originalQueue.enqueue(20);
        
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> movedQueue(std::move(originalQueue));
        
        std::vector<int> expectedMoved = {10, 20};
        EXPECT_TRUE(compare_queues(movedQueue, expectedMoved));
        
        EXPECT_TRUE(originalQueue.empty());
        EXPECT_EQ(originalQueue.get_size(), 0);
    }

    TEST(QueueTests, CopyAssignmentOperatorCopiesQueueCorrectly) {
        FixedBlockMemoryResource customResource(2048);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> queue1(allocator);
        
        queue1.enqueue(5);
        queue1.enqueue(15);
        
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> queue2(allocator);
        queue2.enqueue(25);
        
        queue2 = queue1;
        
        std::vector<int> expected = {5, 15};
        EXPECT_TRUE(compare_queues(queue2, expected));
        
        queue1.enqueue(35);
        std::vector<int> expectedQueue1 = {5, 15, 35};
        std::vector<int> expectedQueue2 = {5, 15};
        EXPECT_TRUE(compare_queues(queue1, expectedQueue1));
        EXPECT_TRUE(compare_queues(queue2, expectedQueue2));
        
        queue1 = queue1;
        EXPECT_TRUE(compare_queues(queue1, expectedQueue1));
    }

    TEST(AllocatorTests, ShouldThrowWhenMemoryPoolIsExhausted) {
        // Создаем ресурс памяти с очень маленьким пулом
        FixedBlockMemoryResource customResource(2);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);
        
        EXPECT_THROW({
            queue.enqueue(1);
            queue.enqueue(2); 
        }, std::bad_alloc);
    }

    TEST(QueueTests, IteratorsRemainValidAfterModifications) {
        FixedBlockMemoryResource customResource(1024);
        std::pmr::polymorphic_allocator<int> allocator(&customResource);
        CustomQueue<int, std::pmr::polymorphic_allocator<int>> queue(allocator);
        
        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);
        
        int sum = 0;
        for(auto it = queue.begin(); it != queue.end(); ++it){
            sum += *it;
            if(*it == 20){
                queue.enqueue(40);
            }
        }
        
        // Проверка суммы и содержимого очереди
        EXPECT_EQ(sum, 100); // 10 + 20 + 30 + 40
        std::vector<int> expected = {10, 20, 30, 40};
        EXPECT_TRUE(compare_queues(queue, expected));
    }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
