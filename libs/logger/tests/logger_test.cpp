#include <gtest/gtest.h>

#include <logger/logger.h>

TEST(logger_test, PrintTest) {
    testing::internal::CaptureStdout();

    Logger logger;
    logger.Print("kekw");

    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "[INFO] kekw\n");
}

TEST(logger_test, PrefixTest) {
    testing::internal::CaptureStdout();

    Logger logger("lol");
    logger.Print("kekw");

    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "[INFO][lol] kekw\n");
}

TEST(logger_test, TaskTest) {
    testing::internal::CaptureStdout();

    Logger logger;
    auto logger2 = logger.CreateTask("Simple task", 1);
    logger.Print("kekw");
    logger2.Print("lol");
    logger2.Print("lol");
    logger.Print("kekw");

    std::string output = testing::internal::GetCapturedStdout();

    std::string result = "[TASK] Simple task\n[INFO] kekw\n[Simple task][INFO] lol\n[INFO] lol\n[INFO] kekw\n";
    ASSERT_EQ(output, result);
}