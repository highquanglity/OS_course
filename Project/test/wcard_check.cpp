#include <iostream>
#include <vector>
#include <string>
#include "../utils/utils.cpp"

void testWCardCheck()
{
    std::vector<std::string> args1 = {"abc", "def", "ghi"};
    bool result1 = wcard_check(args1);
    std::cout << "Test 1: " << (result1 ? "Passed" : "Failed") << std::endl;

    std::vector<std::string> args2 = {"abc", "def*", "ghi"};
    bool result2 = wcard_check(args2);
    std::cout << "Test 2: " << (result2 ? "Passed" : "Failed") << std::endl;

    std::vector<std::string> args3 = {"abc", "def?", "ghi"};
    bool result3 = wcard_check(args3);
    std::cout << "Test 3: " << (result3 ? "Passed" : "Failed") << std::endl;

    std::vector<std::string> args4 = {"abc", "def", "ghi*"};
    bool result4 = wcard_check(args4);
    std::cout << "Test 4: " << (result4 ? "Passed" : "Failed") << std::endl;

    std::vector<std::string> args5 = {"abc", "def", "ghi?"};
    bool result5 = wcard_check(args5);
    std::cout << "Test 5: " << (result5 ? "Passed" : "Failed") << std::endl;

    std::vector<std::string> args6 = {"abc", "def*", "ghi?"};
    bool result6 = wcard_check(args6);
    std::cout << "Test 6: " << (result6 ? "Passed" : "Failed") << std::endl;

    std::vector<std::string> args7 = {"abc", "def?", "ghi*"};
    bool result7 = wcard_check(args7);
    std::cout << "Test 7: " << (result7 ? "Passed" : "Failed") << std::endl;

    std::vector<std::string> args8 = {"abc*", "def?", "ghi*"};
    bool result8 = wcard_check(args8);
    std::cout << "Test 8: " << (result8 ? "Passed" : "Failed") << std::endl;
}

int main()
{
    testWCardCheck();
    return 0;
}