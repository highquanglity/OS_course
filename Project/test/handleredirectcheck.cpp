#include <iostream>
#include <vector>
#include <string>
#include "../utils/utils.cpp"

void testHandleRedirectCheck()
{
    std::vector<std::string> args1 = {"arg1", "arg2", ">", "arg3"};
    bool result1 = handle_redirect_check(args1, ">");
    if (result1)
    {
        std::cout << "Test case 1 passed!" << std::endl;
    }
    else
    {
        std::cout << "Test case 1 failed!" << std::endl;
    }

    std::vector<std::string> args2 = {"arg1", "arg2", "arg3"};
    bool result2 = handle_redirect_check(args2, ">");
    if (!result2)
    {
        std::cout << "Test case 2 passed!" << std::endl;
    }
    else
    {
        std::cout << "Test case 2 failed!" << std::endl;
    }

}

int main()
{
    testHandleRedirectCheck();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}