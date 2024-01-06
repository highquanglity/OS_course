#include <iostream>
#include <cassert>
#include "../utils/utils.cpp"

void testIsInsideQuotes()
{
    std::string str1 = "Hello, \"World\"";
    assert(IsInsideQuotes(str1, 7) == true);

    std::string str2 = "Hello, 'World'";
    assert(IsInsideQuotes(str2, 7) == true);

    std::string str3 = "Hello, World";
    assert(IsInsideQuotes(str3, 7) == false);

    std::string str4 = "\"Hello\", 'World'";
    assert(IsInsideQuotes(str4, 0) == true);

    std::string str5 = "'Hello', \"World\"";
    assert(IsInsideQuotes(str5, 0) == true);

    std::string str6 = "Hello, World";
    assert(IsInsideQuotes(str6, 0) == false);
}

int main()
{
    testIsInsideQuotes();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}