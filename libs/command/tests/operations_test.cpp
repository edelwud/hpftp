#include <gtest/gtest.h>

#include <command/operations.h>

TEST(operations_test, JoinTest) {
    std::vector<std::string> vec({"1+", "1"});
    auto result = Operations::join(vec, "");
    ASSERT_EQ(result, "1+1");

    std::vector<std::string> vec2({"1+", "1", "=2"});
    auto result2 = Operations::join(vec2, "   ");
    ASSERT_EQ(result2, "1+   1   =2");

    std::vector<std::string> vec3({"1+", "1"});
    auto result3 = Operations::join(vec3, "(plus)");
    ASSERT_EQ(result3, "1+(plus)1");
}

TEST(operations_test, SplitTest) {
    std::string string = "Hello, World!";
    auto vec = Operations::split(string, " ");
    ASSERT_EQ(vec, std::vector<std::string>({"Hello,", "World!"}));

    std::string string2 = "Hello, World! 1 2 3   5";
    auto vec2 = Operations::split(string2, " ");
    ASSERT_EQ(vec2, std::vector<std::string>({"Hello,", "World!", "1", "2", "3", "5"}));

    std::string string3 = "Hello!";
    auto vec3 = Operations::split(string3, "");
    ASSERT_EQ(vec3, std::vector<std::string>());
}