#include <gtest/gtest.h>

#include <command/command.h>

TEST(command_test, InitialTest) {
    Command command(CommandList::AUTH);
    ASSERT_EQ(command.Get(), CommandList::AUTH);
}

TEST(command_test, ParseCommandNameTest) {
    Command command(CommandList::AUTH);
    ASSERT_EQ(command.GetName(), "AUTH");
}

TEST(command_test, SetCommandNameTest) {
    Command command(CommandList::AUTH);
    ASSERT_EQ(command.GetName(), "AUTH");

    Command command2("AUTH", { "username" });
    ASSERT_EQ(command2.GetName(), "AUTH");
    ASSERT_EQ(command2.CombineCommand(), "AUTH username");
}

TEST(command_test, CombainCommandTest) {
    Command command(CommandList::AUTH);
    command.SetArgs({ "username" });
    ASSERT_EQ(command.CombineCommand(), "AUTH username");
}