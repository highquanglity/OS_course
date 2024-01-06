#include <iostream>
#include <cassert>
#include "../utils/utils.cpp"

void testExeCmdOutput()
{
    // Test case 1: Command with output
    std::vector<std::string> args1 = {"ls"};
    std::vector<std::string> result1 = exeCmdOutput(args1);
    assert(!result1.empty());
    std::cout << "Output of 'ls' command:" << std::endl;
    for (const auto& line : result1)
    {
        std::cout << line;
    }
    std::cout << std::endl;

    // Test case 2: Command with no output
    std::vector<std::string> args2 = {"echo", "Hello, World!"};
    std::vector<std::string> result2 = exeCmdOutput(args2);
    assert(result2.empty());

    // Test case 3: Invalid command
    std::vector<std::string> args3 = {"invalid_command"};
    std::vector<std::string> result3 = exeCmdOutput(args3);
    assert(result3.empty());
}

int main()
{
    testExeCmdOutput();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}