#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "../utils/utils.cpp"

void testInItalicCmd_check()
{
    std::vector<std::string> args1 = {"`italic`", "normal", "`bold`"};
    bool result1 = InItalicCmd_check(args1);
    assert(result1 == true);

    std::vector<std::string> args2 = {"normal", "text"};
    bool result2 = InItalicCmd_check(args2);
    assert(result2 == false);

    std::vector<std::string> args3 = {"`code`", "`italic`", "`bold`"};
    bool result3 = InItalicCmd_check(args3);
    assert(result3 == true);

    std::vector<std::string> args4 = {};
    bool result4 = InItalicCmd_check(args4);
    assert(result4 == false);
}

int main()
{
    testInItalicCmd_check();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}