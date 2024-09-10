#include <gtest/gtest.h>
#include "../include/swap.h"

TEST(test_01, basic_test_set){
    ASSERT_TRUE(swap("abc") == "bac");
}

TEST(test_02, basic_test_set){
    ASSERT_TRUE(swap("ccc") == "ccc");
}

TEST(test_03, basic_test_set){
    ASSERT_TRUE(swap("abab") == "baba");
}

TEST(test_04, basic_test_set){
    ASSERT_TRUE(swap("aabacbaa") == "bbabcabb");
}

TEST(test_05, basic_test_set){
    ASSERT_TRUE(swap("cbbabc") == "caabac");
}

TEST(test_06, basic_test_set){
    ASSERT_TRUE(swap("a") == "b");
}

TEST(test_07, basic_test_set){
    ASSERT_TRUE(swap("b") == "a");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}