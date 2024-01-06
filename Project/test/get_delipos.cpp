#include <iostream>
#include <cassert>
#include "../utils/utils.cpp"

void testGetDelimiterPositions()
{
    // Test case 1: Single delimiter in the middle
    std::string str1 = "hello,world";
    std::string delimiter1 = ",";
    std::vector<int> positions1 = get_delimeter_positions(str1, delimiter1);
    assert(positions1.size() == 1);
    assert(positions1[0] == 5);

    // Test case 2: Multiple delimiters
    std::string str2 = "apple,banana,orange";
    std::string delimiter2 = ",";
    std::vector<int> positions2 = get_delimeter_positions(str2, delimiter2);
    assert(positions2.size() == 2);
    assert(positions2[0] == 5);
    assert(positions2[1] == 11);

    // Test case 3: No delimiter
    std::string str3 = "no_delimiter";
    std::string delimiter3 = ",";
    std::vector<int> positions3 = get_delimeter_positions(str3, delimiter3);
    assert(positions3.empty());

    // Test case 4: Empty string
    std::string str4 = "";
    std::string delimiter4 = ",";
    std::vector<int> positions4 = get_delimeter_positions(str4, delimiter4);
    assert(positions4.empty());
}

int main()
{
    testGetDelimiterPositions();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}