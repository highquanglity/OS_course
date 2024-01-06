#include <iostream>
#include <cassert>
#include "../utils/utils.cpp"

void testExpandWildcardTokens()
{
    // Test case 1: No wildcard tokens
    {
        std::vector<std::string> tokens = {"hello", "world"};
        std::vector<std::string> expanded_tokens = expandWildcardTokens(tokens);
        assert(expanded_tokens == tokens);
    }

    // Test case 2: Wildcard tokens
    {
        std::vector<std::string> tokens = {"file*.txt", "image?.jpg"};
        std::vector<std::string> expected_expanded_tokens = {"file1.txt", "file2.txt", "image1.jpg", "image2.jpg"};
        std::vector<std::string> expanded_tokens = expandWildcardTokens(tokens);
        assert(expanded_tokens == expected_expanded_tokens);
    }

    // Test case 3: Mixed wildcard and non-wildcard tokens
    {
        std::vector<std::string> tokens = {"file*.txt", "image?.jpg", "document.docx"};
        std::vector<std::string> expected_expanded_tokens = {"file1.txt", "file2.txt", "image1.jpg", "image2.jpg", "document.docx"};
        std::vector<std::string> expanded_tokens = expandWildcardTokens(tokens);
        assert(expanded_tokens == expected_expanded_tokens);
    }
}

int main()
{
    testExpandWildcardTokens();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}