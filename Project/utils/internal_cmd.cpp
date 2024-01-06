#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "internal_cmd.h"

using namespace std;

/**
 * Handles the "cd" command.
 * Changes the current working directory to the specified directory.
 * If no directory is specified, it changes the current working directory to the default directory.
 * If too many arguments are provided, it displays an error message.
 *
 * @param args The arguments passed to the "cd" command.
 */
void handle_cd(const vector<string> &args)
{
    if (args.size() > 2)
    {
        cout << "bash: cd: too many arguments" << endl;
    }
    else if (args.size() == 2)
    {
        if (chdir(args[1].c_str()) == -1)
        {
            perror("chdir");
        }
    }
    else
    {
        vector<string> defaultArgs = {"cd", "/home"};
        if (chdir(defaultArgs[1].c_str()) == -1)
        {
            perror("chdir");
        }
    }
}

/**
 * Prints the current working directory.
 */
void handle_pwd()
{
    char current_dir[1024];
    if (getcwd(current_dir, sizeof(current_dir)) != NULL)
    {
        cout << current_dir << endl;
    }
    else
    {
        perror("getcwd");
    }
}

/**
 * Handles the echo command by printing the arguments to the console.
 *
 * @param args The vector of strings containing the arguments.
 */
void handle_echo(const vector<string> &args)
{
    for (int i = 1; i < args.size(); ++i)
    {
        cout << args[i] << " ";
    }
    cout << endl;
}

/**
 * Displays the available commands and their descriptions.
 */
void handle_help()
{
    cout << "cd [dir] : change directory to dir" << endl;
    cout << "pwd : print current working directory" << endl;
    cout << "echo [args] : print args" << endl;
    cout << "ls [dir] : list files in dir" << endl;
    cout << "cat [file] : print content of file" << endl;
    cout << "exit : exit shell" << endl;
}

/**
 * Handles the "cat" command, which concatenates and displays the contents of one or more files.
 *
 * @param args A vector of strings representing the command-line arguments.
 * @return An integer indicating the success or failure of the command.
 */
int handle_cat(vector<string> &args)
{
    if (args.size() == 1)
    {
        cout << "cat: missing operand" << endl;
        return 1;
    }
    for (int i = 1; i < args.size(); i++)
    {
        FILE *fp;
        char ch;
        fp = fopen(args[i].c_str(), "r");
        if (fp == NULL)
        {
            perror("fopen");
            continue;
        }
        while ((ch = fgetc(fp)) != EOF)
        {
            cout << ch;
        }
        cout<<endl;
        fclose(fp);
    }
    return 1;
}
/**
 * Executes internal commands based on the given arguments.
 *
 * @param args The vector of command arguments.
 * @return 1 if the command is an internal command and executed successfully, 0 otherwise.
 */
int exeInternalCmd(vector<string> &args)
{
    if (args[0] == "cd")
    {
        handle_cd(args);
        return 1;
    }
    else if (args[0] == "pwd")
    {
        handle_pwd();
        return 1;
    }
    else if (args[0] == "echo")
    {
        handle_echo(args);
        return 1;
    }
    else if (args[0] == "help")
    {
        handle_help();
        return 1;
    }
    else if (args[0] == "cat")
    {
        return handle_cat(args);
    }
    else
    {
        return 0;
    }
}