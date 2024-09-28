#include <gtest/gtest.h>
#include "../include/Five.h"

// Tests for constructors
TEST(FiveTest, test_01_default_constructor) {
    Five f;
    ASSERT_EQ(f.get_size(), 1);
    ASSERT_EQ(f.get_data()[0], '0');
}

TEST(FiveTest, test_02_size_and_char_constructor) {
    Five f(3, '2');
    ASSERT_EQ(f.get_size(), 3);
    ASSERT_EQ(f.get_data()[0], '2');
    ASSERT_EQ(f.get_data()[1], '2');
    ASSERT_EQ(f.get_data()[2], '2');
}

TEST(FiveTest, test_03_size_and_char_constructor_2) {
    Five f(5, '4');
    ASSERT_EQ(f.get_size(), 5);
    ASSERT_EQ(f.get_data()[0], '4');
    ASSERT_EQ(f.get_data()[1], '4');
    ASSERT_EQ(f.get_data()[2], '4');
    ASSERT_EQ(f.get_data()[3], '4');
    ASSERT_EQ(f.get_data()[4], '4');
}

TEST(FiveTest, test_04_initializer_list_constructor) {
    Five f = {'1', '2', '3'};
    ASSERT_EQ(f.get_size(), 3);
    ASSERT_EQ(f.get_data()[0], '1');
    ASSERT_EQ(f.get_data()[1], '2');
    ASSERT_EQ(f.get_data()[2], '3');
}

TEST(FiveTest, test_05_initializer_list_constructor_2) {
    Five f = {'4', '3', '2', '1'};
    ASSERT_EQ(f.get_size(), 4);
    ASSERT_EQ(f.get_data()[0], '4');
    ASSERT_EQ(f.get_data()[1], '3');
    ASSERT_EQ(f.get_data()[2], '2');
    ASSERT_EQ(f.get_data()[3], '1');
}

TEST(FiveTest, test_06_initializer_list_constructor_3) {
    Five f = {'0', '0', '0', '0', '0'};
    ASSERT_EQ(f.get_size(), 5);
    ASSERT_EQ(f.get_data()[0], '0');
    ASSERT_EQ(f.get_data()[1], '0');
    ASSERT_EQ(f.get_data()[2], '0');
    ASSERT_EQ(f.get_data()[3], '0');
    ASSERT_EQ(f.get_data()[4], '0');
}

// Tests for assignment operator
TEST(FiveTest, set_assignment_test_01) {
    Five f1 = {'1', '2', '3'};
    Five f2;
    f2 = f1;
    ASSERT_EQ(f2.get_size(), f1.get_size());
    ASSERT_EQ(f2.get_data()[0], f1.get_data()[0]);
    ASSERT_EQ(f2.get_data()[1], f1.get_data()[1]);
    ASSERT_EQ(f2.get_data()[2], f1.get_data()[2]);
}

TEST(FiveTest, set_assignment_test_02) {
    Five f1 = {'4', '3', '2', '1'};
    Five f2;
    f2 = f1;
    ASSERT_EQ(f2.get_size(), f1.get_size());
    ASSERT_EQ(f2.get_data()[0], f1.get_data()[0]);
    ASSERT_EQ(f2.get_data()[1], f1.get_data()[1]);
    ASSERT_EQ(f2.get_data()[2], f1.get_data()[2]);
    ASSERT_EQ(f2.get_data()[3], f1.get_data()[3]);
}

TEST(FiveTest, set_assignment_test_03) {
    Five f1 = {'0', '0', '0', '0', '0'};
    Five f2;
    f2 = f1;
    ASSERT_EQ(f2.get_size(), f1.get_size());
    ASSERT_EQ(f2.get_data()[0], f1.get_data()[0]);
    ASSERT_EQ(f2.get_data()[1], f1.get_data()[1]);
    ASSERT_EQ(f2.get_data()[2], f1.get_data()[2]);
    ASSERT_EQ(f2.get_data()[3], f1.get_data()[3]);
    ASSERT_EQ(f2.get_data()[4], f1.get_data()[4]);
}

// Tests for addition assignment operator
TEST(FiveTest, add_assignment_test_01) {
    Five f1 = {'1', '2', '3'};
    Five f2 = {'4', '2', '1'};
    f1 += f2;
    ASSERT_EQ(f1.get_size(), 4);
    ASSERT_EQ(f1.get_data()[0], '1');
    ASSERT_EQ(f1.get_data()[1], '0');
    ASSERT_EQ(f1.get_data()[2], '4');
    ASSERT_EQ(f1.get_data()[3], '4');
}

TEST(FiveTest, add_assignment_test_02) {
    Five f1 = {'4', '3', '2', '1'};
    Five f2 = {'1', '2', '3', '4'};
    f1 += f2;
    ASSERT_EQ(f1.get_size(), 5);
    ASSERT_EQ(f1.get_data()[0], '1');
    ASSERT_EQ(f1.get_data()[1], '1');
    ASSERT_EQ(f1.get_data()[2], '1');
    ASSERT_EQ(f1.get_data()[3], '1');
    ASSERT_EQ(f1.get_data()[4], '0');
}

TEST(FiveTest, add_assignment_test_03) {
    Five f1 = {'0', '0', '0', '0', '0'};
    Five f2 = {'0', '0', '0', '0', '0'};
    f1 += f2;
    ASSERT_EQ(f1.get_size(), 1);
    ASSERT_EQ(f1.get_data()[0], '0');
}

// Tests for subtraction assignment operator
TEST(FiveTest, sub_assignment_test_01) {
    Five f1 = {'4', '2', '1'};
    Five f2 = {'1', '2', '3'};
    f1 -= f2;
    ASSERT_EQ(f1.get_size(), 3);
    ASSERT_EQ(f1.get_data()[0], '2');
    ASSERT_EQ(f1.get_data()[1], '4');
    ASSERT_EQ(f1.get_data()[2], '3');
}

TEST(FiveTest, sub_assignment_test_02) {
    Five f1 = {'4', '3', '2', '1'};
    Five f2 = {'1', '2', '3', '4'};
    f1 -= f2;
    ASSERT_EQ(f1.get_size(), 4);
    ASSERT_EQ(f1.get_data()[0], '3');
    ASSERT_EQ(f1.get_data()[1], '0');
    ASSERT_EQ(f1.get_data()[2], '3');
    ASSERT_EQ(f1.get_data()[3], '2');
}

TEST(FiveTest, sub_assignment_test_03) {
    Five f1 = {'0', '0', '0', '0', '0'};
    Five f2 = {'0', '0', '0', '0', '0'};
    f1 -= f2;
    ASSERT_EQ(f1.get_size(), 1);
    ASSERT_EQ(f1.get_data()[0], '0');
}

// Tests for comparison operators
TEST(FiveTest, eq_equality_test_01) {
    Five f1 = {'1', '2', '3'};
    Five f2 = {'1', '2', '3'};
    Five f3 = {'4', '2', '1'};
    ASSERT_TRUE(f1 == f2);
    ASSERT_FALSE(f1 == f3);
}

TEST(FiveTest, eq_equality_test_02) {
    Five f1 = {'4', '3', '2', '1'};
    Five f2 = {'4', '3', '2', '1'};
    Five f3 = {'1', '2', '3', '4'};
    ASSERT_TRUE(f1 == f2);
    ASSERT_FALSE(f1 == f3);
}

TEST(FiveTest, eq_equality_test_03) {
    Five f1 = {'0', '0', '0', '0', '0'};
    Five f2 = {'0', '0', '0', '0', '0'};
    Five f3 = {'0', '0', '0', '0', '1'};
    ASSERT_TRUE(f1 == f2);
    ASSERT_FALSE(f1 == f3);
}

TEST(FiveTest, lt_less_than_test_01) {
    Five f1 = {'1', '2', '3'};
    Five f2 = {'4', '2', '1'};
    ASSERT_TRUE(f1 < f2);
    ASSERT_FALSE(f2 < f1);
}

TEST(FiveTest, lt_less_than_test_02) {
    Five f1 = {'4', '3', '2', '1'};
    Five f2 = {'1', '2', '3', '4'};
    ASSERT_FALSE(f1 < f2);
    ASSERT_TRUE(f2 < f1);
}

TEST(FiveTest, lt_less_than_test_03) {
    Five f1 = {'0', '0', '0', '0', '0'};
    Five f2 = {'0', '0', '0', '0', '1'};
    ASSERT_TRUE(f1 < f2);
    ASSERT_FALSE(f2 < f1);
}

TEST(FiveTest, gt_greater_than_test_01) {
    Five f1 = {'4', '2', '1'};
    Five f2 = {'1', '2', '3'};
    ASSERT_TRUE(f1 > f2);
    ASSERT_FALSE(f2 > f1);
}

TEST(FiveTest, gt_greater_than_test_02) {
    Five f1 = {'4', '3', '2', '1'};
    Five f2 = {'1', '2', '3', '4'};
    ASSERT_TRUE(f1 > f2);
    ASSERT_FALSE(f2 > f1);
}

TEST(FiveTest, gt_greater_than_test_03) {
    Five f1 = {'0', '0', '0', '0', '1'};
    Five f2 = {'0', '0', '0', '0', '0'};
    ASSERT_TRUE(f1 > f2);
    ASSERT_FALSE(f2 > f1);
}

TEST(FiveTest, ne_inequality_test_01) {
    Five f1 = {'1', '2', '3'};
    Five f2 = {'4', '2', '1'};
    ASSERT_TRUE(f1 != f2);
    ASSERT_FALSE(f1 != f1);
}

TEST(FiveTest, ne_inequality_test_02) {
    Five f1 = {'4', '3', '2', '1'};
    Five f2 = {'1', '2', '3', '4'};
    ASSERT_TRUE(f1 != f2);
    ASSERT_FALSE(f1 != f1);
}

TEST(FiveTest, ne_inequality_test_03) {
    Five f1 = {'0', '0', '0', '0', '0'};
    Five f2 = {'0', '0', '0', '0', '1'};
    ASSERT_TRUE(f1 != f2);
    ASSERT_FALSE(f1 != f1);
}

// Tests for error handling
TEST(FiveTest, exception_invalid_argument_test_01) {
    ASSERT_THROW(Five f(0, '0'), std::invalid_argument);
}

TEST(FiveTest, exception_invalid_argument_test_02) {
    ASSERT_THROW(Five f(""), std::invalid_argument);
}

TEST(FiveTest, exception_invalid_argument_test_03) {
    ASSERT_THROW(Five f({'1', '2', '5'}), std::invalid_argument);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}