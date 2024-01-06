#include <iostream>
#include <cassert>
#include "../utils/utils.cpp"

void testSingleCmdProcess()
{
    // Test case 1: No quotes or spaces
    std::string cmd1 = "command1";
    std::vector<std::string> tokens1 = single_cmd_process(cmd1);
    assert(tokens1.size() == 1);
    assert(tokens1[0] == "command1");

    // Test case 2: Single quotes
    std::string cmd2 = "command2 'arg1' 'arg2'";
    std::vector<std::string> tokens2 = single_cmd_process(cmd2);
    assert(tokens2.size() == 3);
    assert(tokens2[0] == "command2");
    assert(tokens2[1] == "arg1");
    assert(tokens2[2] == "arg2");

    // Test case 3: Double quotes
    std::string cmd3 = "command3 \"arg1\" \"arg2\"";
    std::vector<std::string> tokens3 = single_cmd_process(cmd3);
    assert(tokens3.size() == 3);
    assert(tokens3[0] == "command3");
    assert(tokens3[1] == "arg1");
    assert(tokens3[2] == "arg2");

    // Test case 4: Mixed quotes
    std::string cmd4 = "command4 'arg1' \"arg2\"";
    std::vector<std::string> tokens4 = single_cmd_process(cmd4);
    assert(tokens4.size() == 3);
    assert(tokens4[0] == "command4");
    assert(tokens4[1] == "arg1");
    assert(tokens4[2] == "arg2");

    // Test case 5: Invalid command
    std::string cmd5 = "command5 'arg1' arg2'";
    std::vector<std::string> tokens5 = single_cmd_process(cmd5);
    assert(tokens5.empty()); // Expecting an empty vector

    // Test case 6: Odd number of quotes
    std::string cmd6 = "command6 'arg1' 'arg2";
    std::vector<std::string> tokens6 = single_cmd_process(cmd6);
    assert(tokens6.empty()); // Expecting an empty vector
}

int main()
{
    testSingleCmdProcess();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}