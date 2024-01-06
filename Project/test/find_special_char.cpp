#include <iostream>
#include <cassert>
#include "../utils/utils.cpp"

void test_find_special_character()
{
    // Test case 1: String contains the special character
    assert(find_special_character("Hello, World!", ",") == true);

    // Test case 2: String does not contain the special character
    assert(find_special_character("Hello, World!", "!") == false);

    // Test case 3: Empty string
    assert(find_special_character("", ",") == false);

    // Test case 4: Special character is an empty string
    assert(find_special_character("Hello, World!", "") == true);

    // Test case 5: Special character is longer than the string
    assert(find_special_character("Hello", "Hello, World!") == false);

    // Add more test cases here...

    std::cout << "All test cases passed!" << std::endl;
}

int main()
{
    test_find_special_character();

    return 0;
}