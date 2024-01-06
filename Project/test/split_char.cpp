#include <iostream>
#include <cassert>
#include "../utils/utils.cpp"

void testSplitCmd_char()
{
    // Test case 1: Single token
    std::string command1 = "hello";
    std::string delimiter1 = " ";
    std::vector<std::string> expected1 = {"hello"};
    std::vector<std::string> result1 = SplitCmd_char(command1, delimiter1);
    assert(result1 == expected1);

    // Test case 2: Multiple tokens
    std::string command2 = "hello world";
    std::string delimiter2 = " ";
    std::vector<std::string> expected2 = {"hello", "world"};
    std::vector<std::string> result2 = SplitCmd_char(command2, delimiter2);
    assert(result2 == expected2);

    // Test case 3: Empty command
    std::string command3 = "";
    std::string delimiter3 = " ";
    std::vector<std::string> expected3 = {};
    std::vector<std::string> result3 = SplitCmd_char(command3, delimiter3);
    assert(result3 == expected3);

    // Test case 4: Custom delimiter
    std::string command4 = "hello|world|test";
    std::string delimiter4 = "|";
    std::vector<std::string> expected4 = {"hello", "world", "test"};
    std::vector<std::string> result4 = SplitCmd_char(command4, delimiter4);
    assert(result4 == expected4);
}

int main()
{
    testSplitCmd_char();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}