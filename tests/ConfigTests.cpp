#include <gtest/gtest.h>
#include <iostream>
#include "../src/Config.hpp"

#define CHECK_FOR_FAILURES_MSG(statement, message)                                                 \
{                                                                                                  \
    SCOPED_TRACE(message);                                                                         \
    ASSERT_NO_FATAL_FAILURE((statement));                                                          \
}

#define CHECK_FOR_FAILURES(statement) CHECK_FOR_FAILURES_MSG(statement, " <--  line of failure\n")

TEST(ConfigTests, OpenFile) {
    Config config;

    CHECK_FOR_FAILURES(config.Open("TestConfig.json"));
}

TEST(ConfigTests, ReadData) {
    Config config;
    config.Open("TestConfig.json");

    CHECK_FOR_FAILURES(config.Read());
}

TEST(ConfigTests, WriteData) {
    Config config;
    config.Open("TestConfig.json");

    ASSERT_EQ(true, config.Write("{}"));
}