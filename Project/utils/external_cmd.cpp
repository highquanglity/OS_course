#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/wait.h>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include "external_cmd.h"

using namespace std;

/**
 * Executes an external command with the given arguments.
 *
 * @param args The vector of strings representing the command and its arguments.
 *
 * @return void
 */
void exeExternalCmd(const vector<string> &args)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        vector<char *> c_args;
        c_args.reserve(args.size() + 1);

        for (const auto &arg : args)
        {
            c_args.push_back(const_cast<char *>(arg.c_str()));
        }
        c_args.push_back(nullptr);

        if (execvp(c_args[0], c_args.data()) == -1)
        {
            cerr << "execvp: " << strerror(errno) << endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            cerr << "waitpid: " << strerror(errno) << endl;
        }
    }
}
