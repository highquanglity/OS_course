#include <iostream>
#include <vector>
#include <cassert>
#include "../utils/utils.cpp"

void testFindAndErase()
{
    std::vector<std::string> args1 = {"-f", "file.txt", "-o", "output.txt"};
    std::string file1 = find_and_erase(args1, "-f");
    assert(file1 == "file.txt");
    assert(args1.size() == 2);
    assert(args1[0] == "-o");
    assert(args1[1] == "output.txt");

    std::vector<std::string> args2 = {"-i", "input.txt"};
    std::string file2 = find_and_erase(args2, "-i");
    assert(file2 == "input.txt");
    assert(args2.empty());

    std::vector<std::string> args3 = {"-o"};
    std::string file3 = find_and_erase(args3, "-o");
    assert(file3.empty());
    assert(args3.empty());

    std::vector<std::string> args4 = {"-f", "file1.txt", "-f", "file2.txt"};
    std::string file4 = find_and_erase(args4, "-f");
    assert(file4 == "file1.txt");
    assert(args4.size() == 2);
    assert(args4[0] == "-f");
    assert(args4[1] == "file2.txt");

    std::vector<std::string> args5 = {"-f"};
    std::string file5 = find_and_erase(args5, "-f");
    assert(file5.empty());
    assert(args5.empty());
}

int main()
{
    testFindAndErase();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}