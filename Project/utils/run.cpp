#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
// Trim function to remove leading and trailing whitespaces
void trim(std::string& str) {
    size_t start = str.find_first_not_of(" \t\n");
    size_t end = str.find_last_not_of(" \t\n");

    if (start != std::string::npos && end != std::string::npos) {
        str = str.substr(start, end - start + 1);
    } else {
        str.clear();
    }
}
vector<string> split_cmd_char(const string &command, const string &delimiter)
{
    vector<string> tokens;
    string token;
    int start = 0;
    int end = command.find(delimiter);
    while (end != string::npos)
    {
        token = command.substr(start, end - start);
        trim(token);
        tokens.push_back(token);
        start = end + delimiter.length();
        end = command.find(delimiter, start);
    }
    token = command.substr(start, end);
    trim(token);
    tokens.push_back(token);
    return tokens;
}
void executeCommand(const std::string& command) {
    // Split the command into tokens
    std::vector<std::string> tokens = split_cmd_char(command, " ");

    // Convert vector of strings to array of char*
    std::vector<char*> args;
    args.reserve(tokens.size() + 1);
    for (const auto& token : tokens) {
        args.push_back(const_cast<char*>(token.c_str()));
    }
    args.push_back(nullptr);

    // Fork a child process
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args.data()) == -1) {
            perror("Execution failed");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        // Parent process
        std::cout << "[" << pid << "] " << command << std::endl;
    } else {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
}


int main() {
    // Example command
    const std::string command = "ls --color=auto & pwd & echo date";

    // Split the command into individual commands
    std::vector<std::string> commands = split_cmd_char(command, "&");

    // Execute each command in the background
    for (const auto& cmd : commands) {
        executeCommand(cmd);
    }

    // Wait for all background processes to finish
    int status;
    while (wait(&status) > 0)
        ;

    return 0;
}
