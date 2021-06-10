#include <gtest/gtest.h>

#include <command/parser.h>

TEST(parser_test, GetCommandCodeTest) {
    Parser parser("AUTH username");
    ASSERT_EQ(parser.GetCommandCode(), CommandList::AUTH);
}

TEST(parser_test, GetCommandArgsTest) {
    Parser parser("AUTH username");
    ASSERT_EQ(parser.GetArgs(), std::vector<std::string>({ "username" }));
}

TEST(parser_test, LoadCommandTest) {
    std::string command = "AUTH username";
    Parser parser(command);
    ASSERT_EQ(parser.LoadCommand(), Command(CommandList::AUTH, { "username" }));
}