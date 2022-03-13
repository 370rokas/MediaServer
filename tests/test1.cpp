#include <gtest/gtest.h>

TEST(test1, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
}