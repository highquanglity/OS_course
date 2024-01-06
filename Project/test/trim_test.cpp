#include <iostream>
#include <cassert>
#include "../utils/utils.cpp"

void testTrim()
{
    std::string str1 = "   hello world   ";
    trim(str1);
    assert(str1 == "hello world");

    std::string str2 = "   hello   ";
    trim(str2);
    assert(str2 == "hello");

    std::string str3 = "   ";
    trim(str3);
    assert(str3.empty());

    std::string str4 = "no spaces";
    trim(str4);
    assert(str4 == "no spaces");

    std::string str5 = "";
    trim(str5);
    assert(str5.empty());

    std::string str6 = "   leading spaces";
    trim(str6);
    assert(str6 == "leading spaces");

    std::string str7 = "trailing spaces   ";
    trim(str7);
    assert(str7 == "trailing spaces");
}

int main()
{
    testTrim();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}