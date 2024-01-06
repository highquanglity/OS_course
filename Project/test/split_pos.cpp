#include <iostream>
#include <cassert>
#include "../utils/utils.cpp"

void testSplitCmd_pos()
{
    std::string command = "Hello, world!";
    std::vector<int> splitPositions = {5, 7, 12};
    std::vector<std::string> expected = {"Hello", ", ", "world!"};
    std::vector<std::string> result = SplitCmd_pos(command, splitPositions);
    assert(result == expected);

    command = "This is a test";
    splitPositions = {4, 7, 9};
    expected = {"This", " is", " a", " test"};
    result = SplitCmd_pos(command, splitPositions);
    assert(result == expected);

    command = "No splits";
    splitPositions = {};
    expected = {"No splits"};
    result = SplitCmd_pos(command, splitPositions);
    assert(result == expected);

    command = "Only one split";
    splitPositions = {5};
    expected = {"Only ", "one split"};
    result = SplitCmd_pos(command, splitPositions);
    assert(result == expected);
}

int main()
{
    testSplitCmd_pos();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}